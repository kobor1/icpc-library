/**
 * Author: Radecki
 * Source: https://github.com/Anadi01/icpc-library/blob/main/lib/text/Manacher-Radecki.cpp
 * Description: Computes palindromic ranges.
 * 	\\ s: \texttt{a \phantom{0} b \phantom{0} a \phantom{0} a \phantom{0} b \phantom{0} a \phantom{0} a \phantom{0} c \phantom{0} a \phantom{0} a \phantom{0} b \phantom{0} b \phantom{0} b \phantom{0} b \phantom{0} a \phantom{0} a}
 * 	\\ r: \texttt{0 0 1 0 0 3 0 0 2 0 0 1 0 0 3 0 0 1 0 0 0 1 1 4 1 1 0 0 0 1 0}
 * Time: O(N)
 * Status: Stress-tested
 */
#pragma once

vi Manacher(string s) {
	vi r(SZ(s) * 2 - 1);
	for(int i=0, m=0, k=0, p=0; i < 2*SZ(s) - 1; m = i++ - 1) {
		while(p < k && i / 2 + r[m] != k) {
			r[i++] = min(r[m--], (k + 1 - p++) / 2); }
		while(k+1 < SZ(s) && p > 0 && s[k+1] == s[p-1]) k++, p--;
		r[i] = (k + 1 - p++) / 2;
	}
	return r;
}
