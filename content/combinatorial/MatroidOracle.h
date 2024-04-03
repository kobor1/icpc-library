/**
 * Author: kobor
 * Date: 2023-12-04
 * License: CC0
 * Source: https://github.com/bqi343/cp-notebook/blob/master/Implementations/content/combinatorial%20(11.2)/MatroidIsect.h
 * Description: Example of simple matroid oracle.
 * Status: tested
 */
#pragma once

struct ColorfulMatroid {
	int C = 0; vi col, used;
	ColorfulMatroid(vi _col) : col(_col) {
		for(auto &c: col) C = max(C, c + 1); }
	void clear() { used = vi(C, 0); }
	void ins(int i) { used[col[i]] = 1; }
	bool indep(int i) { return !used[col[i]]; }
};
