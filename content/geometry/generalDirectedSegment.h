/**
 * Author: kobor
 * Date: 2024-09-11
 * License: CC0
 * Source: own work
 * Description: Segment representation usefull for sweeping.
 * 	Compares two segments at the current time on the sweep line (OY projection).
 * Status: tested on a Pafos task
 */
#pragma once

#include "Point.h"

using P = Point<ll>;
using FP = pair<Frac, Frac>;
FP sweepTime;

struct dirSeg {
    P s, e; int rev;
    dirSeg(P _s, P _e) : s(_s), e(_e), rev(0) {
        if(e < s) swap(s, e), rev = 1;
    }
    Frac getY() const {
        P d = (e - s);
        return !sgn(d.x) ? sweepTime.nd : Frac(s.y) +
            (sweepTime.st - Frac(s.x)) * Frac(e.y - s.y, e.x - s.x);
    }
    int compare(dirSeg b) const {
        auto ay = getY(), by = b.getY();
        if(ay != by) return ay < by ? -1 : 1;
        return (sweepTime.nd < ay ? 1 : -1) *
            sgn((e - s).cross(b.e - b.s));
    }
    bool operator<(dirSeg b) const { return compare(b) == -1; }
    bool operator==(dirSeg b) const { return compare(b) == 0; }
};
