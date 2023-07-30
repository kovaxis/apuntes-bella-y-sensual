#include "line.cpp"
#include "point.cpp"

struct C {
    P o;
    T r;

    C(P o, T r) : o(o), r(r) {}
    C() : C(P(), T()) {}

    // intersects the circle with a line, assuming they intersect
    // the intersections are sorted with respect to the direction of the
    // line
    pair<P, P> line_inter(L l) const {
        P c = l.closest_to(o);
        T c2 = (c - o).magsq();
        P e = sqrt(max(r * r - c2, T())) * l.d.unit();
        return {c - e, c + e};
    }

    // checks whether the given line collides with the circle
    // negative: 2 intersections
    // zero: 1 intersection
    // positive: 0 intersections
    // UNTESTED but very simple
    T line_collide(L l) const {
        T c2 = (l.closest_to(o) - o).magsq();
        return c2 - r * r;
    }

    // calculates the two intersections between two circles
    // the circles must intersect in one or two points!
    // REALLY UNTESTED
    pair<P, P> inter(C h) const {
        P d = h.o - o;
        T c = (r * r - h.r * h.r) / d.magsq();
        return h.line_inter({(1 + c) / 2 * d, d.rot()});
    }

    // check if the given circles intersect
    bool collide(C h) const {
        return (h.o - o).magsq() <= (h.r + r) * (h.r + r);
    }

    // get one of the two tangents that cross through the point
    // the point must not be inside the circle
    // a = -1: cw (relative to the circle) tangent
    // a =  1: ccw (relative to the circle) tangent
    P point_tangent(P p, T a) const {
        T c = r * r / p.magsq();
        return o + c * (p - o) - a * sqrt(c * (1 - c)) * (p - o).rot();
    }

    // get one of the 4 tangents between the two circles
    // a =  1: exterior tangents
    // a = -1: interior tangents (requires no area overlap)
    // b =  1: ccw tangent
    // b = -1: cw tangent
    // the line origin is on this circumference, and the direction
    // is a unit vector towards the other circle
    L tangent(C c, T a, T b) const {
        T dr = a * r - c.r;
        P d = c.o - o;
        P n = (d * dr + b * d.rot() * sqrt(d.magsq() - dr * dr)).unit();
        return {o + n * r, -b * n.rot()};
    }

    // find the circumcircle of the given **non-degenerate** triangle
    static C thru_points(P a, P b, P c) {
        L l((a + b) / 2, (b - a).rot());
        P p = l.intersection(L((a + c) / 2, (c - a).rot()));
        return {p, (p - a).mag()};
    }

    // find the two circles that go through the given point, are tangent
    // to the given line and have radius `r`
    // the point-line distance must be at most `r`!
    // the circles are sorted in the direction of the line
    static pair<C, C> thru_point_line_r(P a, L t, T r) {
        P d = t.d.rot().unit();
        if (d * (a - t.o) < 0) d = -d;
        auto p = C(a, r).line_inter({t.o + d * r, t.d});
        return {{p.first, r}, {p.second, r}};
    }

    // find the two circles that go through the given points and have
    // radius `r`
    // the circles are sorted by angle with respect to the first point
    // the points must be at most at distance `r`!
    static pair<C, C> thru_points_r(P a, P b, T r) {
        auto p = C(a, r).line_inter({(a + b) / 2, (b - a).rot()});
        return {{p.first, r}, {p.second, r}};
    }
};
