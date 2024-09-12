/**
 * Author: kobor
 * Date: 2024-08-24
 * License: CC0
 * Source: own work
 * Description: Basic Formal Power Series operations.
 * Time: O(N \log N)
 * Status: tested on yosupo
 */
#pragma once

#include "Polynomial.h"

struct Poly {
	Poly deriv() {
		vll r(a); FOR(i, 0, SZ(r)) r[i] = r[i] * i % mod;
		if(SZ(r)) r.erase(r.begin());
		return r;
	}
	Poly integr() {
		vll r(a); static vll fac{1};
		rep(i, SZ(fac), SZ(r)) fac.pb(fac[i - 1] * i % mod);
		ll facInv = modinv(fac[SZ(r)]);	
		per(i, 0, SZ(r) - 1) {
			r[i] = r[i] * facInv % mod * fac[i] % mod;
			facInv = facInv * (i + 1) % mod;
		}
		r.insert(r.begin(), 0);
		return r;
	}
	Poly log(int n) { // assert(a[0] == 1);
		return (trim(n).deriv() * inv(n)).integr().trim(n);
	}
	Poly exp(int n) { // assert(a[0] == 0);
		Poly q(1);
		for(int i = 1; i < n; i *= 2) {
			Poly p = Poly(1) + trim(i * 2) - q.log(i * 2);
			q = (q * p).trim(i * 2);
		}
		return q.trim(n);
	}
	Poly pow(ll k, int n) {
		int t = 0; while(t < min(SZ(a), n) && a[t] == 0) t++;
		int shift = min(min(k, (ll)n) * t, (ll)n);
		vll r({a.begin() + t, a.begin() + min(SZ(a), t+n-shift)});
		if(!SZ(r)) return Poly(k == 0);
		ll el0 = r[0], inv0 = modinv(el0), pow0 = modpow(el0, k);
		for(auto &x: r) x = x * inv0 % mod;
		Poly res = Poly(r).log(n - shift);
		for(auto &x: res.a) x = x * (k % mod) % mod;
		res = res.exp(n - shift);
		for(auto &x: res.a) x = x * pow0 % mod;
		res.a.insert(res.a.begin(), shift, 0);
		return res.trim(n);
	}
};
