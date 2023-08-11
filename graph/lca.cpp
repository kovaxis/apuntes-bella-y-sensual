// calculates the lowest common ancestor for any two nodes in O(log N) time,
// with O(N log N) preprocessing
struct Lca {
    int N, K, t = 0;
    vector<vector<int>> U;
    vector<int> L, R;

    Lca() {}
    Lca(vector<vector<int>> &G) : N(G.size()), L(N), R(N) {
        K = N <= 1 ? 0 : 32 - __builtin_clz(N - 1);
        U.resize(K + 1, vector<int>(N));
        visit(G, 0, 0);
        rep(k, K) rep(u, N) U[k + 1][u] = U[k][U[k][u]];
    }

    void visit(vector<vector<int>> &G, int u, int p) {
        L[u] = t++, U[0][u] = p;
        for (int v : G[u]) if (v != p) visit(G, v, u);
        R[u] = t++;
    }

    bool is_anc(int up, int dn) {
        return L[up] <= L[dn] && R[dn] <= R[up];
    }

    int find(int u, int v) {
        if (is_anc(u, v)) return u;
        if (is_anc(v, u)) return v;
        for (int k = K; k >= 0;)
            if (is_anc(U[k][u], v)) k--;
            else u = U[k][u];
        return U[0][u];
    }
};
