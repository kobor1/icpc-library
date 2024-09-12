/**
 * Author: kobor
 * Date: 2019-07-19
 * License: CC0
 * Source: https://github.com/justiceHui/AlgorithmImplement/blob/master/Math/Fast-Kitamasa.cpp
 * Description: Generates the $k$'th term of an $n$-order linear recurrence $a[i] = \sum_j a[i-j-1]c[j]$,
 * 	given $a[0 \ldots \ge n-1]$ and $c[0 \ldots n-1]$.
 * 	Can be generalized to generate many consecutive terms.
 * 	Works \tilde 5s for $N = 10^5$ (using FFTmod).
 * Time: O(N \log N \log K)
 * Status: tested on yosupo
 */
#pragma once

#include "Polynomial.h"

ll linearRecFast(vll a, vll c, ll k) {
	reverse(all(c)); c.pb(-1);
	Poly d(1), xn({0, 1}), f(Poly() - c);
	Poly hf = f.rev().inv(SZ(f.a));	// compute inverse only once
	auto divFast = [&](Poly p) {
		if(SZ(p.a) < SZ(hf.a)) return Poly();
		int sz = SZ(p.a) - SZ(hf.a) + 1;
		Poly ra = p.rev().trim(sz), rb = hf.trim(sz);
		vll res = (ra * rb).a; res.resize(sz); reverse(all(res));
		return Poly(res);
	};
	auto modFast = [&](Poly p) { return p - divFast(p) * f; };
	for(; k; k >>= 1, xn = modFast(xn * xn))
		if(k & 1) d = modFast(d * xn);
	ll res = 0;
	FOR(i, 0, min(SZ(a), SZ(d.a)))
		res = (res + a[i] * d.a[i]) % mod;
	return res;
}
