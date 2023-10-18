// get the area of a simple polygon in ccw order
T area(const vector<P> &ps) {
    int N = ps.size(); T a = 0;
    rep(i, N) a += (ps[i] - ps[0]) % (ps[(i + 1) % N] - ps[i]);
    return a / 2;
}

// checks whether a point is inside a simple polygon
// returns 1 if inside, 0 if on border, -1 if outside
// O(N)
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
                T z = s % e; if (z == 0) return 0;
                if (b == (z > 0)) w += b ? 1 : -1;
            }
        }
    }
    return w ? 1 : -1;
}

// check if point in ccw convex polygon, O(log n)
// + if inside, 0 if on border, - if outside
T in_convex(const vector<P> &p, P q) {
    int l = 1, h = p.size() - 2; assert(p.size() >= 3);
    while (l != h) { // collinear points are unsupported!
        int m = (l + h + 1) / 2;
        if (q.left(p[0], p[m]) >= 0) l = m;
        else h = m - 1;
    }
    T in = min(q.left(p[0], p[1]), q.left(p.back(), p[0]));
    return min(in, q.left(p[l], p[l + 1]));
}

// classify collision of a ray inside a ccw polygon vertex.
// ray is (o, d), vertex is b, previous vertex is a, next is c.
pair<bool, bool> inner_collide(P o, P d, P a, P b, P c) {
    T p = (a - o) % d;       // side of previous
    T n = (c - o) % d;       // side of next
    T v = (c - b) % (b - a); // is vertex convex?
    return {v > 0 ? n < 0 || (n == 0 && p < 0) : p > 0 || n < 0,
            v > 0 ? p > 0 || (p == 0 && n > 0) : p > 0 || n < 0};
}
