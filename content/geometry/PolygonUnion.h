/**
 * Author: black_horse2014, chilli
 * Date: 2019-10-29
 * License: Unknown
 * Source: https://codeforces.com/gym/101673/submission/50481926
 * Description: Calculates the area of the union of $n$ polygons (not necessarily
 * convex). The points within each polygon must be given in CCW order.
 * (Epsilon checks may optionally be added to sideOf/sgn, but shouldn't be needed.)
 * Time: $O(N^2)$, where $N$ is the total number of points
 * Status: stress-tested, Submitted on ECNA 2017 Problem A
 */
#pragma once

#include "Point.h"
#include "sideOf.h"

using P = Point<D>;
D rat(P a, P b) { return sgn(b.x) ? a.x/b.x : a.y/b.y; }
D polyUnion(vector<vector<P>> &poly) {
	D ret = 0;
	FOR(i,0,SZ(poly)) FOR(v,0,SZ(poly[i])) {
		P A = poly[i][v], B = poly[i][(v + 1) % SZ(poly[i])];
		vector<pair<D, int>> segs = {{0, 0}, {1, 0}};
		FOR(j,0,SZ(poly)) if (i != j) {
			FOR(u,0,SZ(poly[j])) {
				P C = poly[j][u], D = poly[j][(u + 1) % SZ(poly[j])];
				int sc = sideOf(A, B, C), sd = sideOf(A, B, D);
				if (sc != sd) {
					D sa = C.cross(D, A), sb = C.cross(D, B);
					if (min(sc, sd) < 0)
						segs.emplace_back(sa / (sa - sb), sgn(sc - sd));
				} else if (!sc && !sd && j<i && sgn((B-A).dot(D-C))>0){
					segs.emplace_back(rat(C - A, B - A), 1);
					segs.emplace_back(rat(D - A, B - A), -1);
				}
			}
		}
		sort(all(segs));
		for (auto &s: segs) s.st = min(max(s.st, 0.0), 1.0);
		D sum = 0;
		int cnt = segs[0].nd;
		FOR(j,1,SZ(segs)) {
			if (!cnt) sum += segs[j].st - segs[j - 1].st;
			cnt += segs[j].nd;
		}
		ret += A.cross(B) * sum;
	}
	return ret / 2;
}
