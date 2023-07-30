// calculate the solvability of a system of logical equations, where every equation is of the form `a or b`.
//  `neg`: get negation of `u`
//  `then`: `u` implies `v`
//  `any`: `u` or `v`
//  `set`: `u` is true
//
// after `solve` (O(V+E)) returns true, `sol` contains one possible solution.
// determining all solutions is O(V*E) hard (requires computing reachability in a DAG).
struct TwoSat {
    int N; vector<vector<int>> G;
    Scc scc; vector<bool> sol;
    TwoSat(int n) : N(n), G(2 * n), sol(n) {}
    TwoSat() {}

    int neg(int u) { return (u + N) % (2 * N); }
    void then(int u, int v) { G[u].push_back(v), G[neg(v)].push_back(neg(u)); }
    void any(int u, int v) { then(neg(u), v); }
    void set(int u) { G[neg(u)].push_back(u); }

    bool solve() {
        scc = Scc(G);
        rep(u, N) if (scc.comp[u] == scc.comp[neg(u)]) return false;
        rep(u, N) sol[u] = (scc.comp[u] > scc.comp[neg(u)]);
        return true;
    }
};
