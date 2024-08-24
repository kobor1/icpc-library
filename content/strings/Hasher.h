/**
 * Author: kobor
 * Date: 2024-03-20
 * License: CC0
 * Source: own work
 * Description: Self-explanatory methods for string hashing.
 * Status: not tested, should work tho
 */
#pragma once

const __int128 C = 2137;
const ll mod = ll(1e18) + 31;

struct Hasher {
	vector<ll> ha, pw;
	Hasher(string &s) : ha(SZ(s) + 1), pw(SZ(s) + 1, 1) {
		FOR(i, 0, SZ(s)) {
			ha[i + 1] = (ha[i] * C + 1 + s[i]) % mod;
			pw[i + 1] = pw[i] * C % mod;
		}
	}
	ll hashInterval(int a, int b) { // hash [a, b]
		ll res = (ha[b+1] - __int128(ha[a]) * pw[b+1 - a]) % mod;
		return res < 0 ? res + mod : res;
	}
};
