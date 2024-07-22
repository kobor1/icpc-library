/**
 * Author: kobor
 * Date: 2024-07-21
 * Source: https://codeforces.com/blog/entry/54150
 * Description: Computes prefix sum $F(x)$ of multiplicative function $f(x)$ using Dirichlet inverse.
 * 	To use it you need to find such a function $g(x)$,
 * 	that for $c(x) = (f * g)(x)$ being their Dirichlet convolution,
 * 	$G(x)$ and $C(x)$ can be quickly calculated.
 * 	As $F(x)$ is multiplicative, standard trick is to compute small values using linear sieve.
 * 	Provided $F(x)$ should work for $x < th$, $G(x)$ and $C(x)$ should work for $x \leq N$.
 * 	Threshold $th$ should be \tilde $N^\frac{2}{3}$ (for single query).
 * 	Hashmap can be changed to simple array (for single query), use $\frac{x}{i}$ as "hash function".
 * Time: O(N^\frac{2}{3})
 * Status: tested on yosupo
 */
#pragma once

const ll mod = 998'244'353;	/** exclude-line */

struct PrefSumMul {
	function<ll(ll)> F, G, C; ll th;
	unordered_map<ll, ll> mem;
	PrefSumMul(auto _F, auto _G, auto _C, ll _th) :
		F(_F), G(_G), C(_C), th(_th) {}
	ll calc(ll x) {
		if(x < th) return F(x);
		auto d = mem.find(x); if(d != mem.end()) return d->nd;
		ll res = 0;
		for(ll i = 2, la; i <= x; i = la + 1) {
			la = x / (x / i);	// largest with same value
			res = (res + (G(la) - G(i-1) + mod) * calc(x/i)) % mod;
		}	// if G(1) != 1 then use modInv there
		return mem[x] = (C(x) - res + mod) / G(1) % mod;
	}
};
