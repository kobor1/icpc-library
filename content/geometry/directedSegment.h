/**
 * Author: kobor
 * Date: 2024-07-15
 * License: CC0
 * Source: own work
 * Description: Segment representation usefull for sweeping.
 * 	Compares two disjoint (can touch) segments on the sweep line (OY projection).
 * 	Transitivity breaks if three segments touch in one point and are on different side of the sweep line.
 * 	Can be easily fixed by comparing mean X coordinates.
 * Status: tested on a few tasks
 */
#pragma once

#include "Point.h"

template<class P>
struct dirSeg {
	P s, e; int rev;
	dirSeg(P _s, P _e) : s(_s), e(_e), rev(0) {
		if(e < s) swap(s, e), rev = 1;
	}
	P getY(P X) {	// takes x * 2, returns y * 2 as a fraction
		P d = (e - s);
		return !sgn(d.x) ? P(s.y+e.y, 1) : P(d.cross(s*2-X), d.x);
	}
	int cmp(dirSeg b) {	// needs ~64 * M^3 !
		P X(max(s.x, b.s.x) + min(e.x, b.e.x), 0);
		return sgn(getY(X).cross(b.getY(X)));
	}
};
