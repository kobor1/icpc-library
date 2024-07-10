/**
 * Author: Emil Lenngren, Simon Lindholm
 * Date: 2011-11-29
 * License: CC0
 * Source: folklore
 * Description: Calculates a valid assignment to boolean variables a, b, c,... to a 2-SAT problem, so that an expression of the type $(a\|\|b)\&\&(!a\|\|c)\&\&(d\|\|!b)\&\&...$ becomes true, or reports that it is unsatisfiable.
 * Negated variables are represented by bit-inversions (\texttt{\tilde{}x}).
 * Usage:
 *  TwoSat ts(number of boolean variables);
 *  ts.either(0, \tilde3); // Var 0 is true or var 3 is false
 *  ts.setValue(2); // Var 2 is true
 *  ts.atMostOne({0,\tilde1,2}); // <= 1 of vars 0, \tilde1 and 2 are true
 *  ts.solve(); // Returns true iff it is solvable
 *  ts.values[0..N-1] holds the assigned values to the vars
 * Time: O(N+E), where N is the number of boolean variables, and E is the number of clauses.
 * Status: stress-tested
 */
#pragma once

struct TwoSat {
	int n; vector<vi> gr; vi values; // 0 = false, 1 = true
	TwoSat(int _n = 0) : n(_n), gr(n * 2) {}

	int addVar() { FOR(i, 0, 2) gr.pb({}); return n++; }

	void either(int f, int j) {
		f = max(2*f, -1-2*f); j = max(2*j, -1-2*j);
		gr[f].pb(j^1); gr[j].pb(f^1);
	}
	
	void setValue(int x) { either(x, x); }

	void atMostOne(const vi& li) { // (optional)
		if(SZ(li) <= 1) return;
		int cur = ~li[0];
		FOR(i, 2, SZ(li)) {
			int next = addVar();
			either(cur, ~li[i]); either(cur, next);
			either(~li[i], next); cur = ~next;
		}
		either(cur, ~li[1]);
	}

	vi val, comp, z; int time = 0;
	int dfs(int i) {
		int low = val[i] = ++time, x; z.pb(i);
		for(int e: gr[i]) if(!comp[e]) {
			low = min(low, val[e] ?: dfs(e)); }
		if(low == val[i]) do {
			x = z.back(); z.pop_back(); comp[x] = low;
			if(values[x >> 1] == -1) values[x >> 1] = x & 1;
		} while(x != i);
		return val[i] = low;
	}

	bool solve() {
		values.assign(n, -1); val.assign(n * 2, 0); comp = val;
		FOR(i, 0, n * 2) if(!comp[i]) dfs(i);
		FOR(i, 0, n) if(comp[2*i] == comp[2*i+1]) return 0;
		return 1;
	}
};
