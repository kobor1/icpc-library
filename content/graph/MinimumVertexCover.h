/**
 * Author: Johan Sannemo, Simon Lindholm
 * Date: 2016-12-15
 * License: CC0
 * Description: Finds a minimum vertex cover in a bipartite graph.
 *  The size is the same as the size of a maximum matching, and
 *  the complement is a maximum independent set.
 * Status: stress-tested
 */
#pragma once

#include "hopcroftKarp.h"

vi cover(vector<vi>& g, int n, int m) {
	vi match(m, -1);
	int res = hopcroftKarp(g, match);
	vector<bool> lfound(n, 1), seen(m);
	for(int it: match) if(it != -1) lfound[it] = 0;
	vi q, cover;
	FOR(i, 0, n) if(lfound[i]) q.pb(i);
	while(!q.empty()) {
		int i = q.back(); q.pop_back(); lfound[i] = 1;
		for(int e: g[i]) if(!seen[e] && match[e] != -1) {
			seen[e] = true; q.pb(match[e]); }
	}
	FOR(i, 0, n) if(!lfound[i]) cover.pb(i);
	FOR(i, 0, m) if(seen[i]) cover.pb(n + i);
	assert(SZ(cover) == res);
	return cover;
}
