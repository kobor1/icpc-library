/**
 * Author: kobor
 * Date: 2023-12-07
 * Description: A short self-balancing tree. It acts as a
 *  sequential container with log-time splits/joins, and
 *  is easy to augment with additional data.
 * Time: $O(\log N)$, increase works in $O(\log N \log U)$ amortized
 * Status: tested on few tasks, but need to be stress-tested
 */
#pragma once

struct Treap {
	struct Node {
		int ch[2] = {0, 0}; 
		int rank = rand(), size = 0;
		int val = 0, mn = 1e9, sum = 0;	// Subtree aggregates
		bool flip = 0; int add = 0;		// Lazy tags
		Node() {}
		Node(int v) : size(1), val(v), mn(v), sum(v) {}
	};
	vector<Node> t;
	Treap() : t(1) {}

	void pull(int v) {
		auto [l, r] = t[v].ch;
		t[v].size = t[l].size + 1 + t[r].size;
		t[v].mn = min({t[l].mn, t[v].val, t[r].mn});
		t[v].sum = t[l].sum + t[v].val + t[r].sum;
	}

	int apply(int v, bool flip, int add) {
		if(!v) return 0;
		// t.pb(t[v]), v = SZ(t) - 1; 			// <- persistency
		if(flip) t[v].flip ^= 1, swap(t[v].ch[0], t[v].ch[1]);
		t[v].val += add; t[v].mn += add;
		t[v].sum += add * t[v].size;
		t[v].add += add;
		return v;
	}

	void push(int v) {
		FOR(i, 0, 2) {
			t[v].ch[i] = apply(t[v].ch[i], t[v].flip, t[v].add);
		}
		t[v].flip = 0; t[v].add = 0;
	}

	pii split(int v, int k) {
		if(!v) return {0, 0};
		push(v);
		auto [l, r] = t[v].ch;
		if(k <= t[l].size) {
		// if(k <= t[v].val) { 					// <- by values
			auto [p, q] = split(l, k);
			t[v].ch[0] = q, pull(v);
			return {p, v};
		}
		else {
			auto [p, q] = split(r, k - t[l].size - 1);
			// auto [p, q] = split(r, k);		// <- by values
			t[v].ch[1] = p, pull(v);
			return {v, q};
		}
	}

	int merge(int v, int u) {
		if(!v || !u) return v ^ u;
		push(v), push(u);
		if(t[v].rank > t[u].rank) {
			t[v].ch[1] = merge(t[v].ch[1], u);
			return pull(v), v;
		}
		else {
			t[u].ch[0] = merge(v, t[u].ch[0]);
			return pull(u), u;
		}
	}

	void insert(int &v, int pos, int val) {
		// if(v) t.pb(t[v]), v = SZ(t) - 1; 	// <- persistency
		auto [p, q] = split(v, pos);
		t.pb(Node(val)); int u = SZ(t) - 1;
		// t.pb(Node(pos)); int u = SZ(t) - 1;	// <- by values
		v = merge(merge(p, u), q);
	}

	void erase(int &v, int l, int r) {
		// if(v) t.pb(t[v]), v = SZ(t) - 1; 	// <- persistency
		auto [p, q] = split(v, l);
		auto [u, s] = split(q, r - l + 1);
		// auto [u, s] = split(q, r + 1);		// <- by values
		v = merge(p, s);
	}

	void modify(int &v, int l, int r, bool flip, int add) {
		// if(v) t.pb(t[v]), v = SZ(t) - 1; 	// <- persistency
		auto [p, q] = split(v, l);
		auto [u, s] = split(q, r - l + 1);
		// auto [u, s] = split(q, r + 1);		// <- by values
		u = apply(u, flip, add);
		v = merge(merge(p, u), s);
	}

	pii get(int &v, int l, int r) {
		// if(v) t.pb(t[v]), v = SZ(t) - 1; 	// <- persistency
		auto [p, q] = split(v, l);
		auto [u, s] = split(q, r - l + 1);
		// auto [u, s] = split(q, r + 1);		// <- by values
		int mn = t[u].mn, sum = t[u].sum;
		v = merge(merge(p, u), s);
		return {mn, sum};
	}

	// only when by values
	int join(int v, int u) {
		if(!v || !u) return v ^ u;
		if(t[v].rank < t[u].rank) swap(v, u);
		auto [p, q] = split(u, t[v].val);
		push(v);
		t[v].ch[0] = join(t[v].ch[0], p);
		t[v].ch[1] = join(t[v].ch[1], q);
		return pull(v), v;
	}

	// only when by values, persistency destroys complexity
	void increase(int &v, int l, int r, int increase) { 
		// if(v) t.pb(t[v]), v = SZ(t) - 1;	// <- persistency
		auto [p, q] = split(v, l);
		auto [u, s] = split(q, r + 1);
		u = apply(u, 0, increase);
		v = join(merge(p, s), u);
	}
};
