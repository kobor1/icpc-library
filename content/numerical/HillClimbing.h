/**
 * Author: Simon Lindholm
 * Date: 2015-02-04
 * License: CC0
 * Source: Johan Sannemo
 * Description: Poor man's optimization for unimodal functions.
 * Status: used with great success
 */
#pragma once

using P = array<double, 2>;
template<class F> pair<double, P> hillClimb(P start, F f) {
	pair<double, P> cur(f(start), start);
	for (double jmp = 1e9; jmp > 1e-20; jmp /= 2) {
		FOR(j,0,100) FOR(dx,-1,2) FOR(dy,-1,2) {
			P p = cur.nd;
			p[0] += dx*jmp;
			p[1] += dy*jmp;
			cur = min(cur, mp(f(p), p));
		}
	}
	return cur;
}
