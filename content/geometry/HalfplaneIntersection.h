/**
 * Author: kobor
 * Date: 2023-12-02
 * License: CC0
 * Source: Petr's blog
 * Description: Checks if half-planes intersection is not empty.
 *  Note that the intersection can be non-empty, despite the area being zero.
 * Time: expected O(n)
 * Status: tested on few tasks with binary search
 */
#pragma once

#include "sideOf.h"
#include "lineIntersection.h"

using P = Point<double>;
pair<int, P> hpInter(vector<pair<P, P>> hps) {
	shuffle(all(hps), mt19937(1337));
	P cand;
	FOR(i, 0, SZ(hps)) {
		auto [s, e] = hps[i];
		if(sideOf(s, e, cand) >= 0) continue;
		P d = (e - s).unit();
		P l = s - d * 1e7, r = s + d * 1e7;
		FOR(j, 0, i) {
			auto [s2, e2] = hps[j];
			auto [res, p] = lineInter(s, e, s2, e2);
			if(res == 1) {
				int cnt = 0;
				if(sideOf(s2, e2, l) == -1) l = p, cnt++;
				if(sideOf(s2, e2, r) == -1) r = p, cnt++;
				if(cnt == 2) return {0, P()};
			}
			else if(sideOf(s2, e2, s) == -1) return {0, P()};
		}
		cand = l;
	}
	return {1, cand};
}