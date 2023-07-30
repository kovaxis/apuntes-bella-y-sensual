#include "point.cpp"

// get the area of a simple polygon in ccw order
// returns negative area for cw polygons
T area(const vector<P> &ps) {
    int N = ps.size();
    T a = 0;
    rep(i, N) a += (ps[i] - ps[0]) / (ps[(i + 1) % N] - ps[i]);
    return a / 2;
}

// checks whether a point is inside a simple polygon
// returns -1 if inside, 0 if on border, 1 if outside
// O(N)
// UNTESTED
int in_poly(const vector<P> &ps, P p) {
    int N = ps.size(), w = 0;
    rep(i, N) {
        P s = ps[i] - p, e = ps[(i + 1) % N] - p;
        if (s == P()) return 0;
        if (s.y == 0 && e.y == 0) {
            if (min(s.x, e.x) <= 0 && 0 <= max(s.x, e.x)) return 0;
        } else {
            bool b = s.y < 0;
            if (b != (e.y < 0)) {
                T z = s / e;
                if (z == 0) return 0;
                if (b == (z > 0)) w += b ? 1 : -1;
            }
        }
    }
    return w ? -1 : 1;
}

// check if a point is in a convex polygon
struct InConvex {
    vector<P> ps;
    T ll, lh, rl, rh;
    int N, m;

    // preprocess polygon
    // O(N)
    InConvex(const vector<P> &p) : ps(p), N(ps.size()), m(0) {
        assert(N >= 2);
        rep(i, N) if (ps[i].x < ps[m].x) m = i;
        rotate(ps.begin(), ps.begin() + m, ps.end());
        rep(i, N) if (ps[i].x > ps[m].x) m = i;
        ll = lh = ps[0].y, rl = rh = ps[m].y;
        for (P p : ps) {
            if (p.x == ps[0].x) ll = min(ll, p.y), lh = max(lh, p.y);
            if (p.x == ps[m].x) rl = min(rl, p.y), rh = max(rh, p.y);
        }
    }
    InConvex() {}

    // check if point belongs in polygon
    // returns -1 if inside, 0 if on border, 1 if outside
    // O(log N)
    int in_poly(P p) {
        if (p.x < ps[0].x || p.x > ps[m].x) return 1;
        if (p.x == ps[0].x) return p.y < ll || p.y > lh;
        if (p.x == ps[m].x) return p.y < rl || p.y > rh;
        int r = upper_bound(ps.begin(), ps.begin() + m, p, [](P a, P b) { return a.x < b.x; }) - ps.begin();
        T z = (ps[r - 1] - ps[r]) / (p - ps[r]);
        if (z >= 0) return !!z;
        r = upper_bound(ps.begin() + m, ps.end(), p, [](P a, P b) { return a.x > b.x; }) - ps.begin();
        z = (ps[r - 1] - ps[r % N]) / (p - ps[r % N]);
        if (z >= 0) return !!z;
        return -1;
    }
};
