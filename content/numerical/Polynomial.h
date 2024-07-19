/**
 * Author: kobor
 * Date: 2024-07-19
 * License: CC0
 * Source: https://github.com/justiceHui/AlgorithmImplement/blob/master/Math/Fast-Kitamasa.cpp
 * Description: Basic polynomial subroutines. Inputs must be in [0, mod).
 * 	Operator \% works \~1s for $N = 5 \cdot 10^5$ (using NTT).
 * 	NTT is rather slow, FFTmod works \~2x faster.
 * Time: O(N \log N)
 * Status: tested on yosupo
 */
#pragma once

#include "NumberTheoreticTransform.h"

struct Poly {
	vll a;
	Poly(ll a0 = 0) : a(1, a0) { normalize(); }
	Poly(vll _a) : a(_a) { normalize(); }
	void normalize() {
		while(SZ(a) && a.back() == 0) a.pop_back();
	}
	Poly rev() { auto b = a; reverse(all(b)); return b; }
	Poly trim(int n) {
		return vll(a.begin(), a.begin() + min(n, SZ(a)));
	}
	Poly inv(int n) {
		Poly q(modpow(a[0], mod - 2));
		for(int i = 1; i < n; i <<= 1) {
			Poly p = Poly(2 % mod) - q * trim(i * 2);
			q = (p * q).trim(i * 2);
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
