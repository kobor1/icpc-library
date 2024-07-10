/**
 * Author: tfg, Aeren, pajenegod, chilli
 * Date: 2020-04-15
 * License: CC0
 * Source: https://codeforces.com/blog/entry/69287
 * Description: Given two matroids, finds the largest common independent set.
 * For the color and graph matroids, this would be the largest forest where no
 * two edges are the same color. A matroid has 3 functions
 *  - check(int x): returns if current matroid can add x without becoming dependent
 *  - add(int x): adds an element to the matroid (guaranteed to never make it dependent)
 *  - clear(): sets the matroid to the empty matroid
 * The matroid is given an int representing the element, and is expected to
 * convert it (e.g: the color or the endpoints)
 * Pass the matroid with more expensive add/clear operations to M1.
 * Time: O(R^2N(M2.add + M1.check + M2.check) + R^3 M1.add + R^2 M1.clear + RN M2.clear)
 * Status: Tested on SWERC 2011D, Pick Your Own Nim
 */
#pragma once

struct ColorMat {
	vi cnt, clr;
	ColorMat(int n, vi _clr) : cnt(n), clr(_clr) {}
	bool check(int x) { return !cnt[clr[x]]; }
	void add(int x) { cnt[clr[x]]++; }
	void clear() { fill(all(cnt), 0); }
};
template <class M1, class M2> struct MatroidIsect {
	int n; vi iset; M1 m1; M2 m2;
	MatroidIsect(M1 _m1, M2 _m2, int _n) :
		n(_n), iset(n + 1), m1(_m1), m2(_m2) {}
	vi solve() {
		per(i, 0, n-1) if(m1.check(i) && m2.check(i)) {
			iset[i] = 1, m1.add(i), m2.add(i);
		}
		while(augment());
		vi ans;
		FOR(i, 0, n) if(iset[i]) ans.pb(i);
		return ans;
	}
	bool augment() {
		vi frm(n, -1); queue<int> q({n}); // starts at dummy node
		auto fwdE = [&](int a) {
			vi ans; m1.clear();
			FOR(v, 0, n) if(iset[v] && v != a) m1.add(v);
			FOR(b, 0, n) if(!iset[b] && frm[b] == -1
				&& m1.check(b)) ans.pb(b), frm[b] = a;
			return ans;
		};
		auto backE = [&](int b) {
			m2.clear();
			FOR(cas, 0, 2) FOR(v, 0, n)
				if((v == b || iset[v]) && (frm[v] == -1) == cas) {
					if(!m2.check(v))
						return cas ? q.push(v), frm[v] = b, v : -1;
					m2.add(v);
				}
			return n;
		};
		while(!q.empty()) {
			int a = q.front(), c; q.pop();
			for(int b: fwdE(a))
				while((c = backE(b)) >= 0) if(c == n) {
					while(b != n) iset[b] ^= 1, b = frm[b];
					return 1;
				}
		}
		return 0;
	}
};
