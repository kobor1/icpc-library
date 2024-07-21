/**
 * Author: kobor
 * Date: 2024-03-22
 * License: CC0
 * Source: own work
 * Description: Builds a centroid tree.
 * Time: O(N \log N)
 * Status: tested
 */
#pragma once

struct CentroidTree {		// 0-indexed
	vector<vector<pii>> G;	// {neighbour, distance}
	vector<ll> dist[LOG];
	vi sz, block, par, dpth;
	CentroidTree(vector<vector<pii>> &_G) : G(_G) {
		int n = SZ(G); sz = block = par = dpth = vi(n);
		FOR(i, 0, LOG) dist[i].resize(n);
		decomp(0, -1);
	}
	void sz_dfs(int v, int p) {
		sz[v] = 1;
		for(auto &[u, _]: G[v]) 
			if(u != p && !block[u]) sz_dfs(u, v), sz[v] += sz[u];
	}
	int find_centr(int v, int p, int sum) {
		for(auto &[u, _]: G[v])
			if(u != p && !block[u] && sz[u] > sum / 2) {
				return find_centr(u, v, sum); }
		return v;
	}
	void dist_dfs(int v, int p, int gleb, ll akt) {
		dist[gleb][v] = akt;
		for(auto &[u, d]: G[v])
			if(u != p && !block[u]) dist_dfs(u, v, gleb, akt + d);
	}
	void decomp(int v, int p) {
		sz_dfs(v, -1); v = find_centr(v, -1, sz[v]);
		par[v] = p;
		if(p != -1) dpth[v] = dpth[p] + 1;
		dist_dfs(v, -1, dpth[v], 0); block[v] = 1;
		for(auto &[u, _]: G[v]) if(!block[u]) decomp(u, v);
	}
};
