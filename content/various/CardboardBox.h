/**
 * Author: kobor
 * Date: 2023-12-04
 * License: CC0
 * Source: https://codeforces.com/contest/436/problem/E
 * Description: Solves task Cardboard Box (can occur on CERC :))
 * Time: O(N \log N)
 * Status: Tested on Cardboard Box
 */
#pragma once

void CardboardBox() {
	int n, w;
	cin >> n >> w;
	vi a(n * 2), vis(n * 2);
	priority_queue<pii> u, v;
	FOR(i, 0, n) {
		cin >> a[i] >> a[i+n];
		a[i+n] -= a[i];
		u.push({-a[i], i});
		v.push({-a[i]-a[i+n], i});
	}
	auto clr = [&](auto &q) {
		while(sz(q) && vis[q.top().nd]) q.pop();
	};
	ll s = 0;
	FOR(jj, 0, w) {
		clr(u), clr(v);
		int i = u.top().nd;
		u.pop(), clr(u);
		if(jj + 1 != w && sz(v) && a[i] - u.top().st > -v.top().st) {
			u.push({-a[i], i}), i = v.top().nd, v.pop();
		}
		if(i < n) u.push({-a[i+n], i+n});
		vis[i] = 1, s += a[i];
	}
	cout << s << '\n';
	FOR(i, 0, n) {
		if(vis[i]) cout << (vis[i+n] ? '2' : '1');
		else cout << '0';
	}
	cout << '\n';
}
