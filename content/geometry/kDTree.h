/**
 * Author: Stanford
 * Date: Unknown
 * Source: Stanford Notebook
 * Description: KD-tree (2d, can be extended to 3d)
 * Status: Tested on excellentengineers
 */
#pragma once

#include "Point.h"

using P = Point<ll>;
const ll INF = 4e18;

bool on_x(const P &a, const P &b) { return a.x < b.x; }
bool on_y(const P &a, const P &b) { return a.y < b.y; }

struct Node {
	P pt; // if this is a leaf, the single point in it
	ll x0 = INF, x1 = -INF, y0 = INF, y1 = -INF; // bounds
	Node *first = 0, *second = 0;
	ll distance(const P& p) { // min squared distance to a point
		ll x = (p.x < x0 ? x0 : p.x > x1 ? x1 : p.x);
		ll y = (p.y < y0 ? y0 : p.y > y1 ? y1 : p.y);
		return (P(x,y) - p).dist2();
	}
	Node(vector<P>&& vp) : pt(vp[0]) {
		for(P p : vp) {
			x0 = min(x0, p.x); x1 = max(x1, p.x);
			y0 = min(y0, p.y); y1 = max(y1, p.y);
		}
		if(SZ(vp) > 1) {
			// split on x if width >= height (not ideal...)
			sort(all(vp), x1 - x0 >= y1 - y0 ? on_x : on_y);
			// divide by taking half the array for each child (not
			// best performance with many duplicates in the middle)
			int half = SZ(vp) / 2;
			first = new Node({vp.begin(), vp.begin() + half});
			second = new Node({vp.begin() + half, vp.end()});
		}
	}
};

struct KDTree {
	Node* root;
	KDTree(const vector<P>& vp) : root(new Node({all(vp)})) {}
	pair<ll, P> search(Node *node, const P& p) {
		if(!node->first) {
			// uncomment if we should not find the point itself:
			// if (p == node->pt) return {INF, P()};
			return mp((p - node->pt).dist2(), node->pt);
		}
		Node *f = node->first, *s = node->second;
		ll bfirst = f->distance(p), bsec = s->distance(p);
		if(bfirst > bsec) swap(bsec, bfirst), swap(f, s);
		// search closest side first, other side if needed
		auto best = search(f, p);
		if(bsec < best.st) best = min(best, search(s, p));
		return best;
	}
	// find nearest point to a point, and its squared distance
	// (requires an arbitrary operator< for Point)
	pair<ll, P> nearest(const P &p) { return search(root, p); }
};
