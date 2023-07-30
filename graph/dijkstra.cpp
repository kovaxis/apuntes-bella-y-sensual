#include "../common.h"

const ll INF = 1e18;

// calculate shortest distances from a source node to every other node in
// O(E log V). requires an array of size N to store results.
void dijkstra(const vector<vector<pair<ll, int>>> &G, vector<ll> &D, int src) {
    priority_queue<pair<ll, int>> q;
    D.assign(G.size(), INF);
    D[src] = 0, q.push({0, src});
    while (!q.empty()) {
        auto [d, u] = q.top();
        d = -d, q.pop();
        if (d > D[u]) continue;
        for (auto [w, v] : G[u])
            if (d + w < D[v]) {
                D[v] = d + w;
                q.push({-D[v], v});
            }
    }
}
