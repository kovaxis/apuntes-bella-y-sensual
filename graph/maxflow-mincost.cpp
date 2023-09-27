// time: O(F V E)            F is the maximum flow
//       O(V E + F E log V)  if bellman-ford is replaced by johnson
struct Flow {
    struct Edge {
        int u, v;
        ll c, w, f = 0;
    };

    int N, s, t;
    vector<vector<int>> G;
    vector<Edge> E;
    vector<ll> d, b;
    vector<int> p;

    Flow() {}
    Flow(int N, int s, int t) : N(N), s(s), t(t), G(N) {}

    void add_edge(int u, int v, ll c, ll w) {
        G[u].push_back(E.size());
        E.push_back({u, v, c, w});
        G[v].push_back(E.size());
        E.push_back({v, u, 0, -w});
    }

    // naive distances with bellman-ford: O(V E)
    void calcdists() {
        p.assign(N, -1), d.assign(N, INF), d[s] = 0;
        rep(i, N - 1) rep(ei, E.size()) {
            Edge &e = E[ei];
            ll n = d[e.u] + e.w;
            if (d[e.u] < INF && e.c - e.f > 0 && n < d[e.v]) d[e.v] = n, p[e.v] = ei;
        }
    }

    // johnsons potentials: O(E log V)
    void calcdists() {
        if (b.empty()) {
            b.assign(N, 0);
            // code below only necessary if there are negative costs
            rep(i, N - 1) rep(ei, E.size()) {
                Edge &e = E[ei];
                if (e.f < e.c) b[e.v] = min(b[e.v], b[e.u] + e.w);
            }
        }
        p.assign(N, -1), d.assign(N, INF), d[s] = 0;
        priority_queue<pair<ll, int>> q;
        q.push({0, s});
        while (!q.empty()) {
            auto [w, u] = q.top();
            q.pop();
            if (d[u] < -w + b[u]) continue;
            for (int ei : G[u]) {
                auto e = E[ei];
                ll n = d[u] + e.w;
                if (e.f < e.c && n < d[e.v]) {
                    d[e.v] = n, p[e.v] = ei;
                    q.push({b[e.v] - n, e.v});
                }
            }
        }
        b = d;
    }

    ll solve() {
        b.clear();
        ll ff = 0;
        while (true) {
            calcdists();
            if (p[t] == -1) break;

            ll f = INF;
            for (int cur = t; p[cur] != -1; cur = E[p[cur]].u)
                f = min(f, E[p[cur]].c - E[p[cur]].f);
            for (int cur = t; p[cur] != -1; cur = E[p[cur]].u)
                E[p[cur]].f += f, E[p[cur] ^ 1].f -= f;
            ff += f;
        }
        return ff;
    }
};