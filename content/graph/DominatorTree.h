/**
 * Author: Anadi
 * Date: 2024-03-21
 * Source: https://github.com/Anadi01/icpc-library/blob/main/lib/graphs/dominatory2.cpp
 * Description: Computes Dominator tree.
 * Status: unknown
 */
#pragma once

struct DominatorTree { // 0-indexed
    int n, t;
    vector<basic_string<int>> g, rg, bucket;
    basic_string<int> arr, par, rev, sdom, dom, dsu, label;
    DominatorTree(int _n) : n(_n), t(0), g(n), rg(n),
        bucket(n), arr(n, -1), par(n, -1), rev(n, -1),
        sdom(n, -1), dom(n, -1), dsu(n, 0), label(n, 0) {}
    void add_edge(int u, int v) { g[u] += v; }
    void dfs(int u) {
        arr[u] = t; rev[t] = u;
        label[t] = sdom[t] = dsu[t] = t; t++;
        for(int w: g[u]) {
            if(arr[w] == -1) dfs(w), par[arr[w]] = arr[u];
            rg[arr[w]] += arr[u];
        }
    }
    int find(int u, int x = 0) {
        if(u == dsu[u]) return x ? -1 : u;
        int v = find(dsu[u], x + 1);
        if(v < 0) return u;
        if(sdom[label[dsu[u]]] < sdom[label[u]]) {
            label[u] = label[dsu[u]]; }
        dsu[u] = v;
        return x ? v : label[u];
    }   // returns -1 for unreachable
    vi run(int root) {
        dfs(root); iota(all(dom), 0);
        per(i, 0, t-1) {
            for(int w: rg[i]) sdom[i] = min(sdom[i], sdom[find(w)]);
            if(i) bucket[sdom[i]] += i;
            for(int w: bucket[i]) {
                int v = find(w);
                if(sdom[v] == sdom[w]) dom[w] = sdom[w];
                else dom[w] = v;
            }
            if(i > 1) dsu[i] = par[i];
        }
        FOR(i, 1, t) if(dom[i] != sdom[i]) dom[i] = dom[dom[i]];
        vi outside_dom(n, -1);
        FOR(i, 1, t) outside_dom[rev[i]] = rev[dom[i]];
        return outside_dom;
    }
};
