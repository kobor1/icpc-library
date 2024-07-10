/**
 * Author: Johan Sannemo
 * Date: 2017-04-18
 * Source: derived from https://gist.github.com/msg555/4963794 by Mark Gordon
 * Description: Computes all faces of the 3-dimension hull of a point set.
 *  *No four points must be coplanar*, or else random results will be returned.
 *  All faces will point outwards.
 * Time: O(n^2)
 * Status: tested on SPOJ CH3D
 */
#pragma once

#include "Point3D.h"

using P3 = Point3D<D>;
struct PR {
	void ins(int x) { (a == -1 ? a : b) = x; }
	void rem(int x) { (a == x ? a : b) = -1; }
	int cnt() { return (a != -1) + (b != -1); }
	int a, b;
};
struct F { P3 q; int a, b, c; };
vector<F> hull3d(const vector<P3> &A) {
	assert(SZ(A) >= 4);
	vector<vector<PR>> E(SZ(A), vector<PR>(SZ(A), {-1, -1}));
#define E(x,y) E[f.x][f.y]
	vector<F> FS;
	auto mf = [&](int i, int j, int k, int l) {
		P3 q = (A[j] - A[i]).cross((A[k] - A[i]));
		if(q.dot(A[l]) > q.dot(A[i])) q = q * -1;
		F f{q, i, j, k};
		E(a,b).ins(k); E(a,c).ins(j); E(b,c).ins(i);
		FS.pb(f);
	};
	FOR(i, 0, 4) FOR(j, i+1, 4) FOR(k, j+1, 4) {
		mf(i, j, k, 6 - i - j - k); }
	FOR(i, 4, SZ(A)) {
		FOR(j, 0, SZ(FS)) {
			F f = FS[j];
			if(f.q.dot(A[i]) > f.q.dot(A[f.a])) {
				E(a,b).rem(f.c); E(a,c).rem(f.b); E(b,c).rem(f.a);
				swap(FS[j--], FS.back()); FS.pop_back();
			}
		}
		int nw = SZ(FS);
		FOR(j,0,nw) {
			F f = FS[j];
#define C(a, b, c) if(E(a,b).cnt() != 2) mf(f.a, f.b, i, f.c);
			C(a, b, c); C(a, c, b); C(b, c, a);
		}
	}
	for (F &it: FS) if((A[it.b] - A[it.a]).cross(
		A[it.c] - A[it.a]).dot(it.q) <= 0) swap(it.c, it.b);
	return FS;
};
