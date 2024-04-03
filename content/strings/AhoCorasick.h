/**
 * Author: Bohun
 * Date: 2024-03-20
 * Source: https://github.com/Anadi01/icpc-library/blob/main/lib/text/Aho-Corasick-Bohun.cpp
 * Description: Famous Bohun's Aho
 * Status: stress-tested
 */
#pragma once

const int N = 1e6 + 5;
int cnt, fail[N], go[N][26];

void add(string s) {
	int u = 0;
	for(auto ch : s) {
		int c = ch - 'a';
		if(!go[u][c]) go[u][c] = ++cnt;
		u = go[u][c];
	}
}

void build() {
	queue<int> q; q.push(0);
	while(!q.empty()) {
		int u = q.front(); q.pop();
		FOR(c, 0, 26) {
			int &v = go[u][c];
			if(v == 0) v = go[fail[u]][c];
			else {
				fail[v] = u == 0 ? 0 : go[fail[u]][c];
				q.push(v);
			}
		}
	}
}
