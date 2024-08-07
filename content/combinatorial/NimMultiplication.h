/**
 * Author: Anadi
 * Date: 2024-03-21
 * Source: https://github.com/Anadi01/icpc-library/blob/main/lib/math/NimMultiplication.cpp
 * Description: Nimber multiplication. To optimize use $(a \oplus b) * c = a * c \oplus b * c$.
 * Time: O((\log N)^{1.58})
 * Status: unknown
 */
#pragma once

using u64 = unsigned long long;
template<int L> inline u64 mulSlow(u64 a, u64 b) {
	static constexpr int l = L >> 1;
	const u64 a0 = a & ((1ull << l) - 1), a1 = a >> l;
	const u64 b0 = b & ((1ull << l) - 1), b1 = b >> l;
	const u64 a0b0 = mulSlow<l>(a0, b0);
	return (a0b0 ^ mulSlow<l>(1ull << (l-1), mulSlow<l>(a1,b1)))
		| (a0b0 ^ mulSlow<l>(a0 ^ a1, b0 ^ b1)) << l;
}
template<> inline u64 mulSlow<1>(u64 a, u64 b) {return a & b;}
