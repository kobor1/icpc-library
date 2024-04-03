/**
 * Author: kobor
 * Date: 2023-12-02
 * License: CC0
 * Source: bicsi's github
 * Description: Data structure that dynamically keeps track
 * of the intersection of half-planes.
 * Time: amortized O(\log n)
 * Status: somewhat tested on few tasks
 */
#pragma once

#include "sideOf.h"
#include "lineIntersection.h"

using P = Point<double>;
int half(P a) { return a.y < 0 || (a.y == 0 && a.x < 0); }

struct polarCmp {
	bool operator()(const P &a, const P &b) const {
		if(half(a) == half(b)) return a.cross(b) > 0;
		return half(a) < half(b);
	}
};

struct HalfplaneSet : map<P, P, polarCmp> {
	double INF = 1e6, area = 8 * INF * INF;	// two times area

	HalfplaneSet() {
		P p(-INF, -INF);
		for(auto &d: {P(1, 0), P(0, 1), P(-1, 0), P(0, -1)}) {
			insert({d, p});
			p = p + d * 2 * INF;
		}
	}

	auto fix(auto it) { return it == end() ? begin() : it; }
	auto getNext(auto it) { return fix(next(it)); }
	auto getPrev(auto it) {
		return it == begin() ? prev(end()) : prev(it);
	}

	auto crossNext(auto it) {
		return it->nd.cross(getNext(it)->nd);
	}

	auto del(auto it) {
		area -= crossNext(getPrev(it)) + crossNext(it);
		it = fix(erase(it));
		if(size()) area += crossNext(getPrev(it));
		return it;
	};

	void add(P s, P e) {
		auto eval = [&](auto it) { return sideOf(s, e, it->nd); };
		auto intersect = [&](auto it) {
			return lineInter(s, e, it->nd, it->st + it->nd).nd;
		};

		auto it = fix(lower_bound(e - s));
		if(empty() || eval(it) >= 0) return;
		while(size() && eval(getPrev(it)) < 0) del(getPrev(it));
		while(size() && eval(getNext(it)) < 0) it = del(it);
		if(empty()) return;
		if(eval(getNext(it)) > 0) {
			area -= crossNext(getPrev(it)) + crossNext(it);
			it->nd = intersect(it);
			area += crossNext(getPrev(it)) + crossNext(it);
		}
		else it = del(it);
		it = getPrev(it);
		area -= crossNext(it);
		insert(it, {e - s, intersect(it)});
		area += crossNext(it) + crossNext(getNext(it));
		if(eval(it) == 0) del(it);
	}

	double maxDot(P a) {
		auto it = fix(lower_bound(a.perp()));
		return a.dot(it->nd);
	}

	double getArea() { return area / 2; }
};