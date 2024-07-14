/**
 * Author: kobor
 * Date: 2024-07-12
 * License: CC0
 * Source: own work
 * Description: Returns area of polygon halfplane intersection.
 * Status: not tested
 */
#pragma once

#include "LineHullIntersection.h"
#include "lineIntersection.h"

using P = Point<D>;
struct PolyCutter {
	vector<D> pArea = {0}; vector<P> poly; int n;
	PolyCutter(vector<P> &_poly) : poly(_poly), n(SZ(poly)) {
		FOR(i, 0, n)
			pArea.pb(pArea.back() + poly[i].cross(poly[(i+1)%n]));
	}
	D cutArea(P a, P b) {
		auto [i, j] = lineHull(a, b, poly);
		if(j == -1 || i == j)
			return cmpL((i + 2) % n) < 0 ? pArea[n] / 2 : 0;
		D res = pArea[i] - pArea[j + 1] + (i < j ? pArea[n] : 0);
		P p = lineInter(poly[i], poly[(i + 1) % n], a, b).nd;
		P q = lineInter(poly[j], poly[(j + 1) % n], a, b).nd;
		res += poly[i].cross(p)+p.cross(q)+q.cross(poly[(j+1)%n]);
		return res / 2;
	}
};
