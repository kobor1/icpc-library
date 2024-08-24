/**
 * Author: kobor
 * Date: 2024-08-24
 * License: CC0
 * Source: own work
 * Description: Basic polynomial subroutines. Inputs must be in [0, mod).
 * 	Empty polynomial is represented as vector of size 1.
 * 	Operator \% works \tilde 1s for $N = 5 \cdot 10^5$ (using NTT).
 * 	NTT is rather slow, FFTmod works \tilde 2x faster.
 * Time: O(N \log N)
 * Status: tested on yosupo
 */
#pragma once

#include "NumberTheoreticTransform.h"

struct Poly {
	vll a;
	Poly(ll a0 = 0) : a(1, a0) {}
	Poly(vll _a) : a(_a) { normalize(); }
	void normalize() {
		while(SZ(a) && a.back() == 0) a.pop_back();
		if(!SZ(a)) a.pb(0);
	}
	Poly rev() { auto b = a; reverse(all(b)); return b; }
	Poly trim(int n) {
		return vll(a.begin(), a.begin() + min(n, SZ(a)));
	}
	Poly inv(int n) {
		Poly q(modinv(a[0]));
		for(int i = 1; i < n; i *= 2) {
			Poly p = Poly(2 % mod) - trim(i * 2) * q;
			q = (q * p).trim(i * 2);
		}
		return q.trim(n);
	}
	Poly operator+(Poly b) {
		vll r(a); r.resize(max(SZ(r), SZ(b.a)));
		FOR(i, 0, SZ(b.a))
			r[i] += b.a[i], r[i] -= r[i] >= mod ? mod : 0;
		return r;
	}
	Poly operator-(Poly b) {
		vll r(a); r.resize(max(SZ(r), SZ(b.a)));
		FOR(i, 0, SZ(b.a))
			r[i] -= b.a[i], r[i] += r[i] < 0 ? mod : 0;
		return r;
	}
	Poly operator*(Poly b) { return Poly(conv(a, b.a)); }
	Poly operator/(Poly b) {
		if(SZ(a) < SZ(b.a)) return Poly();
		int sz = SZ(a) - SZ(b.a) + 1;
		Poly ra = rev().trim(sz), rb = b.rev().trim(sz).inv(sz);
		vll res = (ra * rb).a; res.resize(sz); reverse(all(res));
		return res;
	}
	Poly operator%(Poly b) { return *this - *this / b * b; }
};
