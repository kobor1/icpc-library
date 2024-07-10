/**
 * Author: kobor
 * Date: 2024-03-21
 * Source: https://codeforces.com/blog/entry/63630#comment-475059
 * Description: Fast randomized algorithm for maximum general matching.
 * Status: tested
 */
#pragma once

const int N = 510;
vi g[N]; int lnk[N], vis[N], tim; // 1-indexed

bool dfs(int x) {
	if(!x) return 1;
	vis[x] = tim; random_shuffle(all(g[x]));
	for(int u: g[x]) {
		int v = lnk[u];
		if(vis[v] < tim) {
			lnk[x] = u, lnk[u] = x, lnk[v] = 0;
			if(dfs(v)) return 1;
			lnk[u] = v, lnk[v] = u, lnk[x] = 0; }
	}
	return 0;
}

int max_matching(int n) {
	int ans = 0;	// 20 iterations should also work fine
	FOR(_, 0, 500) rep(i, 1, n) if(!lnk[i]) tim++, ans += dfs(i);
	return ans;
}
