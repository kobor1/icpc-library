/**
 * Author: kobor
 * Date: 2023-12-04
 * License: CC0
 * Source: https://github.com/bqi343/cp-notebook/blob/master/Implementations/content/combinatorial%20(11.2)/MatroidIsect.h
 * Description: Computes a set of maximum size which is independent in both matroids.
 * Time: O(GI^{1.5}) calls to oracles
 * Status: tested
 */
#pragma once

template<class M1, class M2> struct MatroidIsect {
	int n; vi iset; M1 m1; M2 m2;
	bool augment() {
		vi pre(n + 1, -1); queue<int> q({n});
		while(sz(q)) {
			int x = q.front(); q.pop();
			if(iset[x]) {
				m1.clear();
				FOR(i, 0, n) if(iset[i] && i != x) m1.ins(i);
				FOR(i, 0, n) if(!iset[i] && pre[i] == -1 &&
					m1.indep(i)) pre[i] = x, q.push(i);
			}
			else {
				auto backE = [&]() {
					m2.clear();
					FOR(c, 0, 2) FOR(i, 0, n) if((x == i || iset[i]) &&
					(pre[i] == -1) == c) {
						if(!m2.indep(i)) return c ? pre[i] = x, q.push(i), i:-1;
						m2.ins(i);
					}
					return n; 
				};
				for(int y; (y = backE()) != -1;) if(y == n) {
					for(; x != n; x = pre[x]) iset[x] = !iset[x];
					return 1;
				}
			}
		}
		return 0;
	}
	MatroidIsect(int _n, M1 _m1, M2 _m2) : 
	n(_n), m1(_m1), m2(_m2) {
		iset.resize(n + 1), iset[n] = 1;
		m1.clear(); m2.clear();
		for(int i=n-1; i>=0; i--) if(m1.indep(i) && m2.indep(i)) {
			iset[i] = 1, m1.ins(i), m2.ins(i); 
		}
		while (augment());
	}
};
