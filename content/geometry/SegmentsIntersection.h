/**
 * Author: kobor
 * Date: 2024-07-12
 * License: CC0
 * Description: Finds one of the segments intersections.
 * Time: $O(N \log N)$
 * Status: tested on Timus:1469
 */
#pragma once

#include "SegmentIntersection.h"
#include "SegmentXcompare.h"

template<class P>
pii allIntersect(vector<pair<P, P>> a) {
	vector<tuple<P, int, int>> e;
	FOR(i, 0, SZ(a)) {
		if(a[i].nd < a[i].st) swap(a[i].st, a[i].nd);
		e.pb({a[i].st, 0, i}), e.pb({a[i].nd, 1, i});
	}
	sort(all(e));
	auto cmp = [](auto bb, auto cc) {
		auto [bs, be] = bb.st; auto [cs, ce] = cc.st;
		return segXcompare(bs, be, cs, ce);
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
