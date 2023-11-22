/**
 * Author: Simon Lindholm
 * Date: 2016-09-06
 * License: CC0
 * Source: me
 * Description: To get all uniquely determined values of $x$ back from SolveLinear, make the following changes:
 * Status: tested on kattis:equationsolverplus, stress-tested
 */
#pragma once

#include "SolveLinear.h"

FOR(j,0,n) if (j != i) // instead of FOR(j,i+1,n)
// ... then at the end:
x.assign(m, undefined);
FOR(i,0,rank) {
	FOR(j,rank,m) if (fabs(A[i][j]) > eps) goto fail;
	x[col[i]] = b[i] / A[i][i];
fail:; }
