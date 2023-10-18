// time: O(E V^2)
//      O(E V^(2/3)) / O(E sqrt(E))    unit capacities
//      O(E sqrt(V))   (hopcroft-karp) unit networks
//unit network: c in {0,1} & forall v, indeg<=1 or outdeg<=1
//min-cut: nodes reachable from s in final residual graph
struct Dinic {
    struct Edge { int u, v; ll c, f = 0; };
    int N, s, t; vector<vector<int>> G;
    vector<Edge> E; vector<int> lvl, ptr;
    Dinic() {}
    Dinic(int N, int s, int t) : N(N), s(s), t(t), G(N) {}

    void add_edge(int u, int v, ll c) {
        G[u].push_back(E.size()); E.push_back({u, v, c});
        G[v].push_back(E.size()); E.push_back({v, u, 0});
    }

    ll push(int u, ll p) {
        if (u == t || p <= 0) return p;
        while (ptr[u] < G[u].size()) {
            int ei = G[u][ptr[u]++];
            Edge &e = E[ei];
            if (lvl[e.v] != lvl[u] + 1) continue;
            ll a = push(e.v, min(e.c - e.f, p));
            if (a <= 0) continue;
            e.f += a, E[ei ^ 1].f -= a; return a;
        }
        return 0;
    }

    ll maxflow() {
        ll f = 0;
        while (true) {
            lvl.assign(N, -1); queue<int> q;
            lvl[s] = 0; q.push(s);
            while (!q.empty()) {
                int u = q.front(); q.pop();
                for (int ei : G[u]) {
                    Edge &e = E[ei];
                    if (e.c-e.f<=0||lvl[e.v]!=-1) continue;
                    lvl[e.v] = lvl[u] + 1; q.push(e.v);
                }
            }
            if (lvl[t] == -1) break;
            ptr.assign(N,0);while(ll ff=push(s,INF))f += ff;
        }
        return f;
    }
};

/* Flujo con demandas (no necesariamente el maximo)
Agregar s' y t' nuevos source and sink
c'(s', v) = sum(d(u, v) for u in V) \forall arista (s', v)
c'(v, t') = sum(d(v, w) for w in V) \forall arista (v, t')
c'(u, v) = c(u, v) - d(u, v) \forall aristas antiguas
c'(t, s) = INF (el flujo por esta arista es el flujo real)*/