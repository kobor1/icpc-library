/**
 * Author: kobor
 * Date: 2023-12-04
 * License: CC0
 * Source: https://github.com/bqi343/cp-notebook/blob/master/Implementations/content/combinatorial%20(11.2)/MatroidIsect.h
 * Description: Few examples of simple matroid oracles. All of them can be easily optimized.
 * Status: tested
 */
#pragma once

#include "../data-structures/UnionFindRollback.h"

struct GraphicMatroid {
	vector<pii> ed; int V = 0;
	RollbackUF D; // normal UF is fine
	GraphicMatroid(vector<pii> _ed) : ed(_ed), D(0) {
		map<int, int> m;
		for(auto &[a, b]: ed) m[a] = m[b] = 0;
		for(auto &[a, b]: m) b = V++;
		for(auto &[a, b]: ed) a = m[a], b = m[b];
	}
	void clear() { D = RollbackUF(V); }
	void ins(int i) { D.join(ed[i].st, ed[i].nd); }
	bool indep(int i) { 
		return D.find(ed[i].st) != D.find(ed[i].nd);
	}
};

struct ColorfulMatroid {
	int C = 0; vi col, used;
	ColorfulMatroid(vi _col) : col(_col) {
		for(auto &c: col) C = max(C, c + 1);
	}
	void clear() { used = vi(C, 0); }
	void ins(int i) { used[col[i]] = 1; }
	bool indep(int i) { return !used[col[i]]; }
};

struct LinearMatroid {
	vector<ll> elems;
	set<ll, greater<ll>> basis;
	LinearMatroid(vector<ll> _elems) : elems(_elems) {}
	ll reduce(ll x) {
		for(auto &y: basis) x = min(x, x ^ y);
		return x;
	}
	void clear() { basis.clear(); }
	void ins(int i) { basis.insert(reduce(elems[i])); }
	bool indep(int i) { return reduce(elems[i]); }
};
