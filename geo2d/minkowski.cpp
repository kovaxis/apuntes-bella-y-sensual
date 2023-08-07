void reorder_polygon(vector<P> &ps) {
    int pos = 0;
    repx(i, 1, (int)ps.size()) {
        if (ps[i].y < ps[pos].y || (ps[i].y == ps[pos].y && ps[i].x < ps[pos].x))
            pos = i;
    }
    rotate(ps.begin(), ps.begin() + pos, ps.end());
}
vector<P> minkowski(vector<P> ps, vector<P> qs) {
    // the first vertex must be the lowest
    reorder_polygon(ps); reorder_polygon(qs);
    ps.push_back(ps[0]); ps.push_back(ps[1]);
    qs.push_back(qs[0]); qs.push_back(qs[1]);
    vector<P> result; int i = 0, j = 0;
    while (i < ps.size() - 2 || j < qs.size() - 2) {
        result.push_back(ps[i] + qs[j]);
        auto z = (ps[i + 1] - ps[i]) % (qs[j + 1] - qs[j]);
        if (z >= 0 && i < ps.size() - 2) ++i;
        if (z <= 0 && j < qs.size() - 2) ++j;
    }
    return result;
}