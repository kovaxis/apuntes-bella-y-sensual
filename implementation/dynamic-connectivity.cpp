struct DC {
    int n; Dsu D;
    vector<vector<pair<int, int>>> t;
    DC(int N) : n(N), D(N), t(2 * N) {}
    // add edge p to all times in interval [l, r]
    void upd(int l, int r, pair<int, int> p) {
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) t[l++].push_back(p);
            if (r & 1) t[--r].push_back(p);
        }
    }
    void process(int u = 1) { // process all queries
        for (auto &e : t[u]) D.unite(e.first, e.second);
        if (u >= n) {
            // do stuff with D at time u - n
        } else process(2 * u), process(2 * u + 1);
        for (auto &e : t[u]) D.rollback();
    }
};