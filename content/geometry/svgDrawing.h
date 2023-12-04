/**
 * Author: kobor
 * Date: 2023-12-04
 * License: CC0
 * Source: https://github.com/zemen/Jinotega-notebook/blob/master/algo/geometry/svg.cpp
 * Description: Comes in handy when geometry goes brrr.
 * Status: works well
 */
#pragma once

#include "Point.h"

template<class T> struct SVG {
	using P = Point<T>;
    ofstream out; T sc = 10;

    SVG(string name = "image.svg") {
        out.open(name);
        out << "<svg xmlns='http://www.w3.org/2000/svg' viewBox='-1000 -1000 2000 2000'>\n";
    }
    ~SVG() { out << "</svg>\n"; }
    void p(P a, string s = "P") {
        a = a * sc;
        out << "<text x='" << a.x << "' y='" << -a.y << "' font-size='10px'>" << s << "</text>\n";
    }
    void segment(P s, P e) {
        s = s * sc, e = e * sc;
        out << "<line x1='" << s.x << "' y1='" << -s.y << "' x2='" << e.x << "' y2='" << -e.y << "' stroke='black'/>\n";
    }
    void line(P s, P e) {
        T sh = 10;
        segment(s - (e - s) * sh, e + (e - s) * sh);
    }
    void circle(P o, T r) {
        o = o * sc, r = r * sc;
        out << "<circle cx='" << o.x << "' cy='" << -o.y << "' r='" << r << "' stroke='red' stroke-width='1' fill='none'/>\n";
    }
};
