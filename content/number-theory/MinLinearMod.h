/**
 * Author: kobor
 * Date: 2024-07-21
 * License: CC0
 * Source: https://codeforces.com/blog/entry/90690
 * Description: MinRem calculates minimum value of $(ax + b) \pmod{m}$ for $x \in [0, k]$.
 * 	FirstInRange returns minimum $x$ s.t. $(ax + b) \pmod{m} \in [l, r]$.
 * 	If there is no solution, both of them return -1.
 * Time: O(\log m)
 * Status: minRem tested on yosupo
 */
#pragma once

#include "euclid.h"

ll minRem(ll a, ll b, ll m, ll k) {
	if(k < 0) return -1;
	ll g = gcd(a, m);
	if(g > 1) return g * minRem(a/g, b/g, m/g, k) + b % g;
	auto posMod = [](ll x, ll mod) {
		ll res = x % mod; return res < 0 ? res + mod : res;
	};
	auto getSteps = [](ll t, ll ia, ll x, ll mod) {
		return (t - x + mod) * ia % mod;
	};
	for(ll b0 = b, m0 = m, ia0 = modInv(a, m); a;) {
		ll na, nb, nm;
		if(a > m - a) {
			na = a % (m - a); nb = b % (m - a); nm = m - a;
			for(ll steps = getSteps(nb, ia0, b0, m0); steps > k;) {
				ll add = steps - getSteps(nb + nm, ia0, b0, m0);
				return nb + nm * ((steps - k + (add - 1)) / add);
			}
		}
		else {
			na = posMod(-m, a);
			nb = (b < a ? b : posMod(b - m, a)); nm = a;
			if(getSteps(nb, ia0, b0, m0) > k) break;
		}
		a = na; b = nb; m = nm;
	}
	return b;
}

ll firstInRange(ll a, ll b, ll m, ll l, ll r) {
	ll g = gcd(a, m);
	if(g > 1) return firstInRange(a/g, b/g, m/g,
		l/g + (l % g > b % g), r/g - (r % g < b % g));
	ll ia = modInv(a, m);
	return minRem(ia, (l - b + m) * ia % m, m, r - l);
}
