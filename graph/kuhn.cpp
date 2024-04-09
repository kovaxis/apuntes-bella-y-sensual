// get a maximum cardinality matching in a bipartite graph.
// input: adjacency lists.
// output: matching (in `mt` member).
// runtime: O(V E)
struct Kuhn {
    vector<vector<int>> G;
    int N, size;
    vector<bool> seen;
    vector<int> mt;

    bool visit(int i) {
        if (seen[i]) return false;
        seen[i] = true;
        for (int to : G[i])
            if (mt[to] == -1 || visit(mt[to])) {
                mt[to] = i;
                return true;
            }
        return false;
    }

    Kuhn(vector<vector<int>> adj) : G(adj), N(G.size()), mt(N, -1) {
        rep(i, N) {
            seen.assign(N, false);
            size += visit(i);
        }
    }
};
