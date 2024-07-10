/**
 * Author: Simon Lindholm
 * Date: 2015-02-11
 * License: CC0
 * Source: Wikipedia
 * Description: Fast integration using an adaptive Simpson's rule.
 * Usage:
	double sphereVolume = quad(-1, 1, [](double x) {
	return quad(-1, 1, [\&](double y) {
	return quad(-1, 1, [\&](double z) {
	return x*x + y*y + z*z < 1; });});});
 * Status: mostly untested
 */
#pragma once

using D = double;
#define S(a,b) (f(a) + 4*f((a+b) / 2) + f(b)) * (b-a) / 6

template<class F>
D rec(F &f, D a, D b, D eps, D S) {
	D c = (a + b) / 2, S1 = S(a, c), S2 = S(c, b), T = S1 + S2;
	if(abs(T - S) <= 15 * eps || b - a < 1e-10) {
		return T + (T - S) / 15; }
	return rec(f, a, c, eps / 2, S1) + rec(f, c, b, eps / 2, S2);
}
template<class F>
D quad(D a, D b, F f, D eps = 1e-8) {
	return rec(f, a, b, eps, S(a, b));
}
