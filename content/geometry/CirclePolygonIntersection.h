/**
 * Author: chilli, Takanori MAEHARA
 * Date: 2019-10-31
 * License: CC0
 * Source: https://github.com/spaghetti-source/algorithm/blob/master/geometry/_geom.cc#L744
 * Description: Returns the area of the intersection of a circle with a
 * ccw polygon.
 * Time: O(n)
 * Status: Tested on GNYR 2019 Gerrymandering, stress-tested
 */
#pragma once

#include "Point.h"

using P = Point<D>;
#define arg(p, q) atan2(p.cross(q), p.dot(q))
D circlePoly(P c, D r, vector<P> ps) {
	auto tri = [&](P p, P q) {
		auto r2 = r * r / 2;
		P d = q - p;
		auto a = d.dot(p)/d.dist2(), b = (p.dist2()-r*r)/d.dist2();
		auto det = a * a - b;
		if(det <= 0) return arg(p, q) * r2;
		auto s = fmax(0, -a-sqrt(det)), t = fmin(1, -a+sqrt(det));
		if(t < 0 || 1 <= s) return arg(p, q) * r2;
		P u = p + d * s, v = p + d * t;
		return arg(p,u) * r2 + u.cross(v)/2 + arg(v,q) * r2;
	};
	D sum = 0;
	FOR(i, 0, SZ(ps))
		sum += tri(ps[i] - c, ps[(i + 1) % SZ(ps)] - c);
	return sum;
}
