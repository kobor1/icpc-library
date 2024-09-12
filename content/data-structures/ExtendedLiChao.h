/**
 * Author: copy kobor copy
 * Date: 2023-12-17
 * Description: 
 * Supports Range Line Insertion, Range Line Addition, Point Query.
 * Can be modified to support Range Maximum Query,
 * if Line Addition is replaced by Sum Addition.
 * Source: https://codeforces.com/blog/entry/86731
 * Time: $O(\log^2 N)$
 * Status: unknown
 */
#pragma once

template<typename T>
struct Line {
	T a, b;
	Line() : a(0), b(-inf) {}
	Line(T a, T b) : a(a), b(b) {}
	T get(T x) { return a * x + b; }
	void add(Line x) { a += x.a; b += x.b; }
};

struct Node {
	Line<T> line, lazy(0, 0);
	Node *lc = nullptr, *rc = nullptr;
	void apply(T l, T r, Line<T> v) { line.add(v); lazy.add(v); }
};

void PushLazy(Node* &n, T tl, T tr) {
	if(n == nullptr) return;
	if(n->lc == nullptr) n->lc = new Node();
	if(n->rc == nullptr) n->rc = new Node();
	T mid = (tl + tr) / 2;
	n->lc->apply(tl, mid, n->lazy);
	n->rc->apply(mid + 1, tr, n->lazy);
	n->lazy = Line<T>(0, 0);
}

void PushLine(Node* &n, T tl, T tr) {
	if(n == nullptr) return;
	T mid = (tl + tr) / 2;
	InsertLineKnowingly(n->lc, tl, mid, n->line);
	InsertLineKnowingly(n->rc, mid + 1, tr, n->line);
	n->line = Line<T>();
}

void InsertLineKnowingly(Node* &n, T tl, T tr, Line<T> x) {
	if(n == nullptr) n = new Node();
	if(n->line.get(tl) < x.get(tl)) swap(n->line, x);
	if(n->line.get(tr) >= x.get(tr)) return;
	if(tl == tr) return;
	T mid = (tl + tr) / 2;
	PushLazy(n, tl, tr);
	if (n->line.get(mid) > x.get(mid)) {
		InsertLineKnowingly(n->rc, mid + 1, tr, x); }
	else {
		swap(n->line, x);
		InsertLineKnowingly(n->lc, tl, mid, x);
	}
}

void InsertLine(Node* &n, T tl, T tr, T l, T r, Line<T> x) {
	if(tr < l || r < tl || tl > tr || l > r) return;
	if(n == nullptr) n = new Node();
	if(l <= tl && tr <= r) return InsertLineKnowingly(n, tl, tr, x);
	T mid = (tl + tr) / 2;
	PushLazy(n, tl, tr);
	InsertLine(n->lc, tl, mid, l, r, x);
	InsertLine(n->rc, mid + 1, tr, l, r, x);
}

void AddLine(Node* &n, T tl, T tr, T l, T r, Line<T> x) {
	if(tr < l || r < tl || tl > tr || l > r) return;
	if(n == nullptr) n = new Node();
	if(l <= tl && tr <= r) return n->apply(tl, tr, x);
	T mid = (tl + tr) / 2;
	PushLazy(n, tl, tr);
	PushLine(n, tl, tr);
	AddLine(n->lc, tl, mid, l, r, x);
	AddLine(n->rc, mid + 1, tr, l, r, x);
}

T Query(Node* &n, T tl, T tr, T x) {
	if(n == nullptr) return -inf;
	if(tl == tr) return n->line.get(x);
	T res = n->line.get(x);
	T mid = (tl + tr) / 2;
	PushLazy(n, tl, tr);
	if(x <= mid) res = max(res, Query(n->lc, tl, mid, x));
	else res = max(res, Query(n->rc, mid + 1, tr, x));
	return res;
}

void InsertLine(T l, T r, Line<T> x) {
	return InsertLine(root, 0, sz - 1, l, r, x);
}
void AddLine(T l, T r, Line<T> x) {
	return AddLine(root, 0, sz - 1, l, r, x);
}
T Query(T x) { return Query(root, 0, sz - 1, x); }
