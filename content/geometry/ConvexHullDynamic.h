/**
 * Author: kobor
 * Date: 2024-07-27
 * License: CC0
 * Source: bicsi's submit
 * Description: Dynamic convex hull, can be used for computing onion layers.
 *  Insertions also can be implemented, but should be known in advance.
 * 	Points on the edges are included in the hull.
 * Time: O(\log^2 n)
 * Status: tested on yosupo
 */
#pragma once

#include "Point.h"

template<class P>
struct DynHull {
	struct Node { int bl, br, l, r, lc, rc; };
	vector<Node> t = {{-1, -1, -1, -1, 0, 0}};
	vector<P> p; int root; vi mapp, remapp;
	DynHull(vector<P> _p, bool lower = 1) : p(_p) {
		vector<pair<P, int>> pts;
		FOR(i, 0, SZ(p)) pts.pb({(lower ? P() - p[i] : p[i]), i});
		sort(all(pts)); mapp = remapp = vi(SZ(pts));
		FOR(i, 0, SZ(p)) {
			tie(p[i], remapp[i]) = pts[i], mapp[remapp[i]] = i;
		}
		root = build(0, SZ(p) - 1);
	}
	bool leaf(int x) { return t[x].l == t[x].r; }
	int combine(int lc, int rc, int ret = -1) {
		if(!lc || !rc) return lc + rc;
		if(ret == -1 || ret == lc || ret == rc) {
			ret = SZ(t), t.pb({}); }
		t[ret] = {-1, -1, t[lc].l, t[rc].r, lc, rc};
		while(!leaf(lc) || !leaf(rc)) {
			int a = t[lc].bl, b = t[lc].br;
			int c = t[rc].bl, d = t[rc].br;
			if(a != b && p[a].cross(p[b], p[c]) > 0) lc = t[lc].lc;
			else if(c != d && p[b].cross(p[c], p[d]) > 0) {
				rc = t[rc].rc; }
	  		else if(a == b) rc = t[rc].lc;
			else if(c == d) lc = t[lc].rc;
			else {
				auto s1 = p[a].cross(p[b], p[c]);
				auto s2 = p[a].cross(p[b], p[d]);
				assert(s1 >= s2);
				auto xc = p[c].x, xd = p[d].x, xm = p[t[rc].l].x;
				if(s1 == s2 || s1 * xd - s2 * xc < (s1 - s2) * xm) {
					lc = t[lc].rc; }
				else rc = t[rc].lc;
			}
		}
		t[ret].bl = t[lc].l; t[ret].br = t[rc].l;
		return ret;
	}
	int build(int l, int r) {
		if(l == r) { t.pb({l, l, l, l, 0, 0}); return SZ(t) - 1; }
		int mid = (l + r) / 2;
		return combine(build(l, mid), build(mid + 1, r));
	}
	int erase(int v, int pos) {
		if(!v || t[v].r < pos || t[v].l > pos) return v;
		return leaf(v) ? 0 :
			combine(erase(t[v].lc, pos), erase(t[v].rc, pos), v);
	}
	void hull(int v, vi &res, int l = 0, int r = 1e9) {
		if(!v || l > r) return;
		if(leaf(v)) return res.pb(t[v].l);
		hull(t[v].lc, res, l, min(r, t[v].bl));
		hull(t[v].rc, res, max(l, t[v].br), r);
	}
	void erase(int pos) { root = erase(root, mapp[pos]); }
	vi hull() {
		vi res; hull(root, res); for(auto &x: res) x = remapp[x];
		reverse(all(res)); return res;
	}
};
