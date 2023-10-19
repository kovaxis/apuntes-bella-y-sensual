// get TWICE the area of a simple polygon in ccw order
T area2(const vector<P> &p) {
    int n = p.size(); T a = 0;
    rep(i, n) a += (p[i] - p[0]) % (p[(i + 1) % n] - p[i]);
    return a;
}

// checks whether a point is inside a ccw simple polygon
// returns 1 if inside, 0 if on border, -1 if outside
int in_poly(const vector<P> &p, P q) {
    int w = 0;
    rep(i, p.size()) {
        P a = p[i], b = p[(i + 1) % p.size()];
        T k = (b - a) % (q - a);
        T u = a.y - q.y, v = b.y - q.y;
        if (k > 0 && u < 0 && v >= 0) w++;
        if (k < 0 && v < 0 && u >= 0) w--;
        if (k == 0 && (q - a) * (q - b) <= 0) return 0;
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

int extremal(const vector<P> &p, P d) {
    int n = p.size(), l = 0, r = n - 1; assert(n);
    P e0 = (p[n - 1] - p[0]).rot();
    while (l < r) {  // polygon must be convex
        int m = (l + r + 1) / 2;
        P e = (p[(m + n - 1) % n] - p[m]).rot();
        if (e0.angcmp_rel(d, e) < 0) r = m - 1;
        else l = m;
    }
    return l;
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
