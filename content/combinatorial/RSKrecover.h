/**
 * Author: Benq, kobor
 * Date: 2024-07-25
 * License: CC0
 * Source: https://github.com/bqi343/cp-notebook/blob/master/Implementations/content/combinatorial%20(11.2)/RSKrecover.h
 * Description: Recovers $k$ increasing disjoint subsequences, which cover
 * 	the maximum possible number of elements from permutation $pi$.
 * Time: O(NM), where $M$ is the length of the output
 * Status: unknown
 */
#pragma once

vector<vi> RSKrecover(vi pi, int k) {
	int n = SZ(pi); vector<vi> h;
	vector<tuple<int, int, int>> swaps;
	for(auto x: pi) FOR(j, 0, k) {
		if(j >= SZ(h)) h.pb({});
		if(!SZ(h[j]) || h[j].back() < x) { h[j].pb(x); break; }
		per(y, 0, SZ(h[j])-1) {
			if(y == 0 || h[j][y-1] < x) { swap(x, h[j][y]); break; }
			swaps.pb({x, h[j][y-1], h[j][y]});
		}
	}
	vi nxt(n + 1, -1), prv(n + 1, -1);
	FOR(i, 0, SZ(h)) {
		prv[h[i][0]] = n;
		FOR(j, 1, SZ(h[i])) {
			int b = h[i][j-1], c = h[i][j]; nxt[b] = c, prv[c] = b;
		}
		nxt[h[i].back()] = n;
	}
	reverse(all(swaps));
	for(auto &[x, y, z]: swaps) {
		if(nxt[x] != z) continue;
		if(nxt[y] == -1) {
			prv[y] = prv[x]; nxt[prv[y]] = y; nxt[y] = z;
			prv[z] = y; prv[x] = nxt[x] = -1;
		}
		else {
			nxt[x] = nxt[y]; prv[nxt[x]] = x;
			nxt[y] = z; prv[z] = y;
		}
	}
	int cnt = 0; vi seq(n, -1); vector<vi> res(k);
	FOR(i, 0, n) if(prv[i] != -1) {
		seq[i] = prv[i] == n ? cnt++ : seq[prv[i]];
		res[seq[i]].pb(i);
	}
	return res;
}
