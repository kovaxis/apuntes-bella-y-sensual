#include "../common.h"

// calculates the lowest common ancestor for any two nodes in O(log N) time,
// with O(N log N) preprocessing
struct Lca {
    int L;
    vector<vector<int>> up;
    vector<pair<int, int>> time;

    Lca() {}
    void init(const vector<vector<int>> &G) {
        int N = G.size();
        L = N <= 1 ? 0 : 32 - __builtin_clz(N - 1);
        up.resize(L + 1);
        rep(l, L + 1) up[l].resize(N);
        time.resize(N);
        int t = 0;
        visit(G, 0, 0, t);
        rep(l, L) rep(i, N) up[l + 1][i] = up[l][up[l][i]];
    }

    void visit(const vector<vector<int>> &G, int i, int p, int &t) {
        up[0][i] = p;
        time[i].first = t++;
        for (int edge : G[i]) {
            if (edge == p) continue;
            visit(G, edge, i, t);
        }
        time[i].second = t++;
    }

    bool is_anc(int up, int dn) {
        return time[up].first <= time[dn].first &&
               time[dn].second <= time[up].second;
    }

    int get(int i, int j) {
        if (is_anc(i, j)) return i;
        if (is_anc(j, i)) return j;
        int l = L;
        while (l >= 0) {
            if (is_anc(up[l][i], j))
                l--;
            else
                i = up[l][i];
        }
        return up[0][i];
    }
};
