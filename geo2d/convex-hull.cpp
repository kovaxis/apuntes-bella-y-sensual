// ccw order, excludes collinear points by default
vector<P> chull(vector<P> p) {
    if (p.size() < 3) return p;
    vector<P> r; int m, k = 0;
    sort(p.begin(), p.end(), [](P a, P b) {
        return a.x != b.x ? a.x < b.x : a.y < b.y; });
    for (P q : p) { // lower hull
        while (k >= 2 && r[k - 1].left(r[k - 2], q) >= 0)
            r.pop_back(), k--; // >= to > to add collinears
        r.push_back(q), k++;
    }
    if (k == (int)p.size()) return r;
    r.pop_back(), k--, m = k;
    for (int i = p.size() - 1; i >= 0; --i) { // upper hull
        while (k >= m+2 && r[k-1].left(r[k-2], p[i]) >= 0)
            r.pop_back(), k--; // >= to > to add collinears
        r.push_back(p[i]), k++;
    }
    r.pop_back(); return r;
}