/**
 * Author: Simon Lindholm
 * Date: 2016-07-24
 * License: CC0
 * Source: Russian page
 * Description: Pre-computation of modular inverses. Assumes LIM $\le$ mod and that mod is a prime.
 * Status: Works
 */
#pragma once

// const ll mod = 1000'000'007, LIM = 200'000; ///include-line
ll* inv = new ll[LIM] - 1; inv[1] = 1;
FOR(i,2,LIM) inv[i] = mod - (mod / i) * inv[mod % i] % mod;