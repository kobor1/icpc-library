/**
 * Author: Goorkiewicz
 * Date: 2024-03-21
 * Source: https://github.com/Anadi01/icpc-library/blob/main/lib/math/polydiv.cpp
 * Description: Pseudocode for polynomial division.
 * Status: unknown
 */
#pragma once

vi polydiv(vi a, vi b) {
	int n = SZ(a), m = SZ(b);
	if(m > n) return {0};
	reverse(all(a)), reverse(all(b));
	int s = moddiv(1, b[0], MOD);
	for(int &x : b) x = modmul(x, s, MOD);
	int k = n - m + 1;
	vi r, v, g = {1};
	for (int w = 1; (1 << (w - 1)) < k; w++){
		r = polymul(g, g); r.resize(1 << w);
		v = b; v.resize(1 << w);
		r = polymul(r, v);
		r.resize(1 << w); g.resize(1 << w);
		polyadd(g, g); polysub(g, r);
	}
	g = polymul(g, a); g.resize(k);
	reverse(all(g));
	for(int &x : g) x = modmul(x, s, MOD);
	return g;
}
