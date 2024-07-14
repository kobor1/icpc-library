/**
 * Author: kobor
 * Date: 2024-07-12
 * Description: 
	* A string is "simple" if it is strictly smaller than any of its own nontrivial suffixes.
	* The Lyndon factorization of the string $s$ is a factorization $s=w_1w_2\ldots w_k$
	* where all strings $w_i$ are simple and $w_1\ge w_2\ge \cdots \ge w_k.$ Min rotation
	* gets min index i such that cyclic shift of s starting at i is minimum.
 * Source: https://cp-algorithms.com/string/lyndon_factorization.html
 * Time: O(N)
 */
#pragma once

vector<string> duval(string s) {
	vector<string> facts;
	for(int i = 0; i < SZ(s); ) {
		int j = i + 1, k = i;
		while(j < SZ(s) && s[k] <= s[j]) {
			if(s[k] < s[j++]) k = i;
			else k++;
		}
		for(; i <= k; i += j-k) facts.pb(s.substr(i, j-k));
	}
	return facts;
}

int minRotation(string s) {
	vector<string> d = duval(s + s); int ind = 0, ans = 0;
	while(ans + SZ(d[ind]) < SZ(s)) ans += SZ(d[ind++]);
	while(ind && d[ind] == d[ind-1]) ans -= SZ(d[ind--]);
	return ans;
}
