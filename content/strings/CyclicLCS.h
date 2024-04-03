/**
 * Author: copy kobor copy
 * Date: 2023-12-17
 * Description: Cyclic Longest Common Subsequence.
	* maximum of lcs(any cyclic shift of s, any cyclic shift of t)
 * Time: $O(NM)$
 */
#pragma once

const int N = 2010;

int dp[N * 2][N], from[N * 2][N];
int cyclic_lcs(string s, string t) {
	int n = SZ(s), m = SZ(t);
	auto eq = [&](int a, int b) {
		return s[(a - 1) % n] == t[(b - 1) % m];
	};
	dp[0][0] = from[0][0] = 0;
	rep(i, 0, n * 2) rep(j, 0, m) {
		dp[i][j] = 0;
		if (j && dp[i][j - 1] > dp[i][j]) {
			dp[i][j] = dp[i][j - 1];
			from[i][j] = 0;
		}
		if (i && j && eq(i, j) && dp[i - 1][j - 1] + 1 > dp[i][j]) {
			dp[i][j] = dp[i - 1][j - 1] + 1;
			from[i][j] = 1;
		}
		if (i && dp[i - 1][j] > dp[i][j]) {
			dp[i][j] = dp[i - 1][j];
			from[i][j] = 2;
		}
	}
	int ret = 0;
	FOR(i, 0, n) {
		ret = max(ret, dp[i + n][m]);
		// re-root
		int x = i + 1, y = 0;
		while (y <= m && from[x][y] == 0) ++y;
		for (; y <= m && x <= n * 2; ++x) {
			from[x][y] = 0, --dp[x][m];
			if (x == n * 2) break;
			for (; y <= m; ++y) {
				if (from[x + 1][y] == 2) break;
				if (y + 1 <= m && from[x + 1][y + 1] == 1) {
					++y; break;
				}
			}
		}
	}
	return ret;
}
