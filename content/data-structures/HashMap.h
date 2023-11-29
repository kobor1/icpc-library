/**
 * Author: Simon Lindholm, chilli
 * Date: 2018-07-23
 * License: CC0
 * Source: http://codeforces.com/blog/entry/60737
 * Description: Hash map with mostly the same API as unordered\_map, but \tilde
 * 3x faster. Uses 1.5x memory.
 * Initial capacity must be a power of 2 (if provided).
 */
#pragma once

#include <ext/pb_ds/assoc_container.hpp> /** keep-include */
#include <ext/pb_ds/tree_policy.hpp> /** keep-include */
using namespace __gnu_pbds;
// For places where hacking might be a problem:
const int R = chrono::high_resolution_clock::
now().time_since_epoch().count();
struct chash { // To use most bits rather than just the lowest
	const uint64_t C = ll(4e18 * acos(0)) | 71;
	ll operator()(ll x) const { 
		return __builtin_bswap64((x^R)*C); }
};
// 1 << 16 is initial size, don't put it if you want small map
gp_hash_table<ll, int, chash> h({},{},{},{}, {1 << 16});