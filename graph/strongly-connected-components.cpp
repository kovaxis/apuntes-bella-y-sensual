/* time: O(V + E), memory: O(V)
after building:
    comp = map from vertex to component
          (components are toposorted, root first, leaf last)
    N = number of components
    G = condensation graph (component DAG)
byproducts:
    vgi = transposed graph
    order = reverse topological sort (leaf first, root last)
others:
    vn = number of vertices
    vg = original vertex graph          */
struct Scc {
    int vn, N;
    vector<int> order, comp;
    vector<vector<int>> vg, vgi, G;
    void toposort(int u) {
        if (comp[u]) return;
        comp[u] = -1;
        for (int v : vg[u]) toposort(v);
        order.push_back(u);
    }
    bool carve(int u) {
        if (comp[u] != -1) return false;
        comp[u] = N;
        for (int v : vgi[u]) {
            carve(v);
            if (comp[v] != N) G[comp[v]].push_back(N);
        }
        return true;
    }
    Scc() {}
    Scc(vector<vector<int>> &g)
     : vn(g.size()), vg(g), comp(vn), vgi(vn), G(vn), N(0) {
        rep(u, vn) toposort(u);
        rep(u, vn) for (int v : vg[u]) vgi[v].push_back(u);
        invrep(i, vn) N += carve(order[i]);
    }
};