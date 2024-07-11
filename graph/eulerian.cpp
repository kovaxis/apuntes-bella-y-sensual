// path/tour for directed graphs. uncomment for undirected.
struct Euler {
    struct Edge { int v, rev; };
    vector<vector<Edge>> G; vector<Edge> P;
    Euler(int N = 0) : G(N) {}
    void add_edge(int u, int v) {
        G[u].push_back({v, (int)G[v].size()});
        // G[v].push_back({u, (int)G[u].size() - 1});
    }

    void go(int u) {
        while (G[u].size()) {
            Edge e = G[u].back(); G[u].pop_back();
            // if (e.v == -1) continue;
            // G[e.v][e.rev].v = -1;
            go(e.v); P.push_back(e);
        }
    }

    // works ONLY if the vertex degrees are eulerian! check!
    vector<Edge> get_path(int u) {
        return P.clear(),go(u),reverse(P.begin(),P.end()),P;
    }
};