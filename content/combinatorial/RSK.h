/**
 * Author: mango_lassi, kobor
 * Date: 2024-07-25
 * License: CC0
 * Source: https://codeforces.com/blog/entry/98167
 * Description: Computes mapping from permutations to pairs of normalised Young diagrams (Robinson-Schensted correspondence).
 * 	Properties of this mapping are described in Young diagram section.
 * Time: O(N \sqrt N \log N)
 * Status: tested for n <= 10
 */
#pragma once

vector<vi> boundedRSK(vi pi, int k) {
	vector<vi> res;
	for(auto x: pi) FOR(j, 0, k) {
		if(j >= SZ(res)) res.pb({});
		int pos = lower_bound(all(res[j]), x) - res[j].begin();
		if(pos == SZ(res[j])) { res[j].pb(x); break; }
		swap(x, res[j][pos]);
	}
	return res;
}

pair<vector<vi>, vector<vi>> fastRSK(vi pi) {
	int n = SZ(pi), sq = sqrt(n) + 1;
	vi invPi(n); FOR(i, 0, n) invPi[pi[i]] = i;
	auto p = boundedRSK(pi, sq), q = boundedRSK(invPi, sq);
	reverse(all(pi)), reverse(all(invPi));
	auto pCol = boundedRSK(pi, sq), qCol = boundedRSK(invPi, sq);
	if(n > 0) p.resize(SZ(pCol[0])), q.resize(SZ(qCol[0]));
	FOR(i, sq, SZ(p)) FOR(j, 0, SZ(pCol)) {
		if(SZ(pCol[j]) <= i) break;
		p[i].pb(pCol[j][i]), q[i].pb(qCol[j][i]);
	}
	return {p, q};
}
