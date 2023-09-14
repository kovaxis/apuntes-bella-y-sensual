struct Hld {
    vector<int> P, H, D, pos, top;

    Hld() {}
    void init(vector<vector<int>> &G) {
        int N = G.size();
        P.resize(N), H.resize(N), D.resize(N), pos.resize(N),
            top.resize(N);
        D[0] = -1, dfs(G, 0); int t = 0;
        rep(i, N) if (H[P[i]] != i) {
            int j = i;
            while (j != -1)
                { top[j] = i, pos[j] = t++; j = H[j]; }
        }
    }

    int dfs(vector<vector<int>> &G, int i) {
        int w = 1, mw = 0;
        D[i] = D[P[i]] + 1, H[i] = -1;
        for (int c : G[i]) {
            if (c == P[i]) continue;
            P[c] = i; int sw = dfs(G, c); w += sw;
            if (sw > mw) H[i] = c, mw = sw;
        }
        return w;
    }

    // visit the log N segments in the path from u to v
    template <class OP>
    void path(int u, int v, OP op) {
        while (top[u] != top[v]) {
            if (D[top[u]] > D[top[v]]) swap(u, v);
            op(pos[top[v]], pos[v] + 1); v = P[top[v]];
        }
        if (D[u] > D[v]) swap(u, v);
        op(pos[u], pos[v] + 1); // value on node
        // op(pos[u]+1, pos[v] + 1); // value on edge
    }

    // an alternative to `path` that considers order.
    // calls `op` with an `l <= r` inclusive-exclusive range, and a
    // boolean indicating if the query is forwards or backwards.
    template <class OP>
    void path(int u, int v, OP op) {
        int lu = u, lv = v;
        while (top[lu] != top[lv])
            if (D[top[lu]] > D[top[lv]]) lu = P[top[lu]];
            else lv = P[top[lv]];
        int lca = D[lu] > D[lv] ? lv : lu;

        while (top[u] != top[lca])
            op(pos[top[u]], pos[u] + 1, false), u = P[top[u]];
        if (u != lca) op(pos[lca] + 1, pos[u] + 1, false);

        vector<int> stk;
        while (top[v] != top[lca])
            stk.push_back(v), v = P[top[v]];

        // op(pos[lca], pos[v] + 1, true);  // value on node
        op(pos[lca] + 1, pos[v] + 1, true); // value on edge
        reverse(stk.begin(), stk.end());
        for (int w : stk) op(pos[top[w]], pos[w] + 1, true);
    }

    // commutative segment tree
    template <class T, class S>
    void update(S &seg, int i, T val) { seg.update(pos[i], val); }

    // commutative segment tree lazy
    template <class T, class S>
    void update(S &seg, int u, int v, T val) {
        path(u, v, [&](int l, int r) { seg.update(l, r, val); });
    }

    // commutative (lazy) segment tree
    template <class T, class S>
    T query(S &seg, int u, int v) {
        T ans = 0;                                                 // neutral element
        path(u, v, [&](int l, int r) { ans += seg.query(l, r); }); // query op
        return ans;
    }
};