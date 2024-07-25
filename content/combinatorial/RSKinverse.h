/**
 * Author: mango_lassi, kobor
 * Date: 2024-07-25
 * License: CC0
 * Source: https://codeforces.com/blog/entry/98167
 * Description: Computes inverse of mapping from permutations to pairs of normalised Young diagrams (Robinson-Schensted correspondence).
 * Time: O(N^2)
 * Status: tested for n <= 10
 */
#pragma once

vi RSKinverse(vector<vi> p, vector<vi> q) {
	int n = 0; for(auto &x: p) n += SZ(x);
	vi pi(n);
	per(ind, 0, n-1) {
		int i, j;
		for(i = 0; i < SZ(q); i++) {
			for(j = 0; j < SZ(q[i]); j++) if(q[i][j] == ind) break;
			if(j < SZ(q[i])) break;
		}
		int x = p[i][j]; p[i].pop_back(), q[i].pop_back();
		for(i--; i >= 0; i--) {
			j = lower_bound(all(p[i]), x) - p[i].begin();
			swap(p[i][j - 1], x);
		}
		pi[ind] = x;
	}
	return pi;
}
