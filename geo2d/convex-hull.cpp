// ccw order, excludes collinear points by default
// adding collinears duplicates points
vector<P> chull(vector<P> p) {
    if (p.size() < 3) return p;
    vector<P> r; int k = 0;
    sort(p.begin(), p.end(), [](P a, P b) {
        return a.x != b.x ? a.x < b.x : a.y < b.y; });
    for (P q : p) { // lower hull
        while (k >= 2 && r[k - 1].left(r[k - 2], q) >= 0)
            r.pop_back(), k--; // >= to > to add collinears
        r.push_back(q), k++;
    }
    r.pop_back(), k--; int m = k;
    for (int i = p.size() - 1; i >= 0; --i) { // upper hull
        while (k >= m+2 && r[k-1].left(r[k-2], p[i]) >= 0)
            r.pop_back(), k--; // >= to > to add collinears
        r.push_back(p[i]), k++;
    }
    r.pop_back(); return r;
}