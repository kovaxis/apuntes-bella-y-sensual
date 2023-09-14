// calculate distances between every pair of nodes in O(V^3) time.
// works with negative edges, but not negative cycles.
void floyd(const vector<vector<pair<ll, int>>> &G, vector<vector<ll>> &D) {
    int N = G.size();
    D.assign(N, vector<ll>(N, INF));
    rep(u, N) D[u][u] = 0;
    rep(u, N) for (auto [w, v] : G[u]) D[u][v] = w;
    rep(k, N) rep(u, N) rep(v, N)
        D[u][v] = min(D[u][v], D[u][k] + D[k][v]);
}
