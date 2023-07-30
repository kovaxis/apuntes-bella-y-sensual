// untested

#include "../common.h"

const ll INF = 1e18;

struct Edge {
    int u, v;
    ll c, w, f = 0;
};

// find the minimum-cost flow among all maximum-flow flows.
//
// time: O(F V E)            F is the maximum flow
//       O(V E + F E log V)  if bellman-ford is replaced by johnson
struct Flow {
    int N, s, t;
    vector<vector<int>> G;
    vector<Edge> E;
    vector<ll> d;
    vector<int> p;

    Flow() {}
    Flow(int N, int s, int t) : N(N), s(s), t(t), G(N) {}

    void add_edge(int u, int v, ll c, ll w) {
        G[u].push_back(E.size());
        E.push_back({u, v, c, w});
        G[v].push_back(E.size());
        E.push_back({v, u, 0, -w});
    }

    void calcdists() {
        // replace bellman-ford with johnson for better time
        d.assign(N, INF);
        p.assign(N, -1);
        d[s] = 0;
        rep(i, N - 1) rep(ei, E.size()) {
            Edge &e = E[ei];
            ll n = d[e.u] + e.w;
            if (d[e.u] < INF && e.c - e.f > 0 && n < d[e.v]) d[e.v] = n, p[e.v] = ei;
        }
    }

    ll maxflow() {
        ll ff = 0;
        while (true) {
            calcdists();
            if (p[t] == -1) break;

            ll f = INF;
            int cur = t;
            while (p[cur] != -1) {
                Edge &e = E[p[cur]];
                f = min(f, e.c - e.f);
                cur = e.u;
            }

            int cur = t;
            while (p[cur] != -1) {
                E[p[cur]].f += f;
                E[p[cur] ^ 1].f -= f;
            }

            ff += f;
        }
        return ff;
    }
};