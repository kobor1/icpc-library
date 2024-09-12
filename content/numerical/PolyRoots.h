/**
 * Author: Per Austrin
 * Date: 2004-02-08
 * License: CC0
 * Description: Finds the real roots to a polynomial.
 * Usage: polyRoots({{2,-3,1}},-1e9,1e9) // solve x^2-3x+2 = 0
 * Time: O(n^2 \log(1/\epsilon))
 */
#pragma once

#include "Poly.h"

vector<D> polyRoots(Poly p, D xmin, D xmax) {
	if(SZ(p.a) == 2) { return {-p.a[0]/p.a[1]}; }
	vector<D> ret;
	Poly der = p; der.diff();
	auto dr = polyRoots(der, xmin, xmax);
	dr.pb(xmin-1); dr.pb(xmax+1);
	sort(all(dr));
	FOR(i, 0, SZ(dr)-1) {
		D l = dr[i], h = dr[i+1];
		bool sign = p(l) > 0;
		if(sign ^ (p(h) > 0)) {
			FOR(it, 0, 60) { // while (h - l > 1e-8)
				D m = (l + h) / 2, f = p(m);
				if((f <= 0) ^ sign) l = m;
				else h = m;
			}
			ret.pb((l + h) / 2);
		}
	}
	return ret;
}
