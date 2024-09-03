/**
 * Author: Bohun
 * Date: 2024-03-20
 * License: Unknown
 * Source: https://github.com/Anadi01/icpc-library/blob/main/lib/text/SuffixArray-Bohun.cpp
 * Description: Builds suffix array for a string.
 * \texttt{sa[i]} is the starting index of the suffix which
 * is $i$'th in the sorted suffix array.
 * The returned vector is of size $n+1$, and \texttt{sa[0] = n}.
 * The \texttt{lcp} array contains longest common prefixes for
 * neighbouring strings in the suffix array.
 * Time: O(n \log n)
 * Status: stress-tested
 */
#pragma once

const int N = 1e6 + 5; /// exclude-line
int s[N]; /* s[i] > 0, n = len(s), A = sigma(s) */
int n, A, sa[N], lcp[N], cnt[N];
vi x, y;

bool dif(int a, int b, int k) {
	return y[a] != y[b] ||
	(a + k <= n ? y[a + k] : -1) != (b + k <= n ? y[b + k] : -1);
}
/* 1-indexed */
void build() {
	x.clear(); x.resize(max(A, n) + 2); y = x; // +2 enough?
	int j = 0;
	rep(i, 0, A) cnt[i] = 0;
	rep(i, 1, n) cnt[x[i] = s[i]]++;
	rep(i, 1, A) cnt[i] += cnt[i - 1];
	per(i, 1, n) sa[cnt[x[i]]--] = i;    
	for(int k = 1; k < n; k *= 2) {
		int p = 0;
		rep(i, n - k + 1, n) y[++p] = i;
		rep(i, 1, n) if(sa[i] > k) y[++p] = sa[i] - k;
		rep(i, 1, A) cnt[i] = 0;
		rep(i, 1, n) cnt[x[i]]++;
		rep(i, 1, A) cnt[i] += cnt[i - 1];
		per(i, 1, n) sa[cnt[x[y[i]]]--] = y[i];
		swap(x, y); A = x[sa[1]] = 1;
		rep(i, 2, n) x[sa[i]] = (A += dif(sa[i - 1], sa[i], k));
		if(n == A) break; 
	}
	rep(i, 1, n) {
		if(x[i] == n) { lcp[x[i]] = 0; continue; }
		int nxt = sa[x[i] + 1];
		while(max(i, nxt) + j <= n && s[i + j] == s[nxt + j]) j++;
		lcp[x[i]] = j; j = max(j - 1, 0);
	}
}
