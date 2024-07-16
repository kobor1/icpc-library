/**
 * Author: kobor
 * Date: 2024-07-12
 * License: CC0
 * Description: Finds one of segments intersections.
 *	You should change dirSeg's comparator, to compare segments at their left end.
 * Time: $O(N \log N)$
 * Status: tested on Timus:1469
 */
#pragma once

#include "SegmentIntersection.h"
#include "directedSegment.h"

template<class P>
pii segmentsIntersect(vector<pair<P, P>> segments) {
	vector<tuple<P, int, int>> eve; // {point, event_type, id}
	vector<dirSeg<P>> segs;
	for(auto &[s, e]: segments) {
		dirSeg<P> seg(s, e);
		eve.pb({seg.s,0,SZ(segs)}), eve.pb({seg.e,1,SZ(segs)});
		segs.pb(seg);
	}
	sort(all(eve));
	auto inter = [](auto a, auto b) {
		return SZ(segInter(a->st.s, a->st.e, b->st.s, b->st.e));
	};
	auto cmp = [](auto a, auto b) {
		return mp(a.st.cmp(b.st), a.nd) < mp(0, b.nd);
	};
	set<pair<dirSeg<P>, int>, decltype(cmp)> s(cmp);
	for(auto &[_, eve_tp, id]: eve) {
		if(eve_tp == 0) {	// add segment
			auto it = s.insert({segs[id], id}).st;
			if(next(it) != s.end() && inter(it, next(it)))
				return {it->nd, next(it)->nd};
			if(it != s.begin() && inter(it, prev(it)))
				return {it->nd, prev(it)->nd};
		}
		if(eve_tp == 1) {	// del segment
			auto it = s.erase(s.find({segs[id], id}));
			if(it!=s.begin() && it!=s.end() && inter(it, prev(it)))
				return {it->nd, prev(it)->nd};
		}
	}
	return {-1, -1};
}
