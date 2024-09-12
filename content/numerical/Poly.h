/**
 * Author: David Rydh, Per Austrin
 * Date: 2003-03-16
 * Description:
 */
#pragma once

using D = double;
struct Poly {
	vector<D> a;
	D operator()(D x) const {
		D val = 0; for(int i = SZ(a); i--;) (val *= x) += a[i];
		return val;
	}
	void diff() {
		FOR(i, 1, SZ(a)) a[i-1] = i * a[i];
		a.pop_back();
	}
	void divroot(D x0) {
		D b = a.back(), c; a.back() = 0;
		for(int i=SZ(a)-1; i--;) c = a[i], a[i] = a[i+1]*x0+b, b=c;
		a.pop_back();
	}
};
