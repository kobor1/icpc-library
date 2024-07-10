/**
 * Author: kobor
 * Date: 2024-06-26
 * License: CC0
 * Source: own work
 * Description: Returns the area of the sum of circles.
 * Time: O(n^2 \log n)
 * Status: Tested on a few tasks
 */
#pragma once

#include "CircleIntersection.h"

D circlesArea(vector<pair<P, D>> c) {
	const D PI = acos((D)-1);
	sort(all(c)); c.erase(unique(all(c)), c.end());
	D res = 0;
	for(auto &[p, r]: c) {
		int cnt = 0, cover = 0;
		vector<pair<D, int>> eve = {{-PI, 0}};
		for(auto &[q, s]: c) if(mp(p, r) != mp(q, s)) {
			D dst = (p - q).dist();
			if(r + dst <= s) { cover = 1; break; }
			pair<P, P> inters;
			if(!circleInter(p, q, r, s, &inters)) continue;
			D le = (inters.st - p).angle();
			D re = (inters.nd - p).angle();
			cnt += le > re;
			eve.pb({le, 1}), eve.pb({re, -1});
		}
		if(cover) continue;
		sort(eve.begin() + 1, eve.end());
		eve.pb({PI, 0});
		D loc = 0;
		FOR(i, 1, SZ(eve)) {
			if(!cnt) {
				D a = eve[i-1].st, b = eve[i].st;
				loc += r * (b - a) +
					p.cross(P(cos(b)-cos(a), sin(b)-sin(a)));
			}
			cnt += eve[i].nd;
		}
		res += r * loc;
	}
	return res / 2;
}
