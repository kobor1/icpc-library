/**
 * Author: kobor
 * Date: 2024-03-22
 * License: CC0
 * Description: Finds one of the segments intersections.
 * Time: $O(N \log N)$
 * Status: tested on Timus:1469
 */
#pragma once

#include "SegmentIntersection.h"

template<class T>
pii allIntersect(vector<pair<Point<T>, Point<T>>> a) {
	using P = Point<T>;
	vector<tuple<P, int, int>> e;
	FOR(i, 0, SZ(a)) {
		if(a[i].nd < a[i].st) swap(a[i].st, a[i].nd);
		e.pb({a[i].st, 0, i}), e.pb({a[i].nd, 1, i});
	}
	sort(all(e));
	auto cmp = [](auto bb, auto cc) {
		auto [bs, be] = bb.st;
		auto [cs, ce] = cc.st;
		P sh(max(bs.x, cs.x), 0);
		auto bv = be - bs, cv = ce - cs;
		T l = bv.cross(bs - sh), r = cv.cross(cs - sh);
		// care! M^3
		return (sgn(cv.x) ? cv.x : 1) * (sgn(bv.x) ? l : bs.y) <
			   (sgn(bv.x) ? bv.x : 1) * (sgn(cv.x) ? r : cs.y);
	};
	auto inter = [](auto bb, auto cc) {
		return segInter(bb.st, bb.nd, cc.st, cc.nd);
	};
	set<pair<pair<P, P>, int>, decltype(cmp)> s(cmp);
	for(auto &[_, tp, id]: e) {
		auto akt = a[id];
		if(!tp) {
			auto it = s.lower_bound({akt, id});
			if(it != end(s) && SZ(inter(it->st, akt)))
				return {it->nd, id};
			if(it != begin(s) && SZ(inter((*--it).st, akt)))
				return {it->nd, id};
			s.insert({akt, id});
		}
		else {
			auto it = s.erase(s.find({akt, id}));
			if(it != begin(s) && it != end(s) &&
				SZ(inter(it->st, prev(it)->st)))
				return {it->nd, prev(it)->nd};
		}
	}
	return {-1, -1};
}
