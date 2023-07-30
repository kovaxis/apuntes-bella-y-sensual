#include "../common.h"

const ll INF = 1e18;

// calculate distances between every pair of nodes in O(V^3) time and O(V^2)
// memory.
// requires an NxN array to store results.
// works with negative edges, but not negative cycles.
void floyd(const vector<vector<pair<int, ll>>> &G, vector<vector<ll>> &dists) {
    int N = G.size();
    rep(i, N) rep(j, N) dists[i][j] = i == j ? 0 : INF;
    rep(i, N) for (auto edge : G[i]) dists[i][edge.first] = edge.second;
    rep(k, N) rep(i, N) rep(j, N) {
        dists[i][j] = min(dists[i][j], dists[i][k] + dists[k][j]);
    }
}
