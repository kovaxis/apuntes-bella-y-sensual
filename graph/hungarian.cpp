// find a maximum gain perfect matching in the given bipartite complete graph.
// input: gain matrix (G_{xy} = benefit of joining vertex x in set X with vertex
// y in set Y).
// output: maximum gain matching in members `xy[x]` and `yx[y]`.
// runtime: O(N^3)
struct Hungarian {
    int N, qi, root;
    vector<vector<ll>> gain;
    vector<int> xy, yx, p, q, slackx;
    vector<ll> lx, ly, slack;
    vector<bool> S, T;

    void add(int x, int px) {
        S[x] = true, p[x] = px;
        rep(y, N) if (lx[x] + ly[y] - gain[x][y] < slack[y]) {
            slack[y] = lx[x] + ly[y] - gain[x][y], slackx[y] = x;
        }
    }

    void augment(int x, int y) {
        while (x != -2) {
            yx[y] = x; swap(xy[x], y); x = p[x];
        }
    }

    void improve() {
        S.assign(N, false), T.assign(N, false), p.assign(N, -1);
        qi = 0, q.clear();
        rep(x, N) if (xy[x] == -1) {
            q.push_back(root = x), p[x] = -2, S[x] = true;
            break;
        }
        rep(y, N) slack[y] = lx[root] + ly[y] - gain[root][y], slackx[y] = root;

        while (true) {
            while (qi < q.size()) {
                int x = q[qi++];
                rep(y, N) if (lx[x] + ly[y] == gain[x][y] && !T[y]) {
                    if (yx[y] == -1) return augment(x, y);
                    T[y] = true, q.push_back(yx[y]), add(yx[y], x);
                }
            }

            ll d = INF;
            rep(y, N) if (!T[y]) d = min(d, slack[y]);
            rep(x, N) if (S[x]) lx[x] -= d;
            rep(y, N) if (T[y]) ly[y] += d;
            rep(y, N) if (!T[y]) slack[y] -= d;

            rep(y, N) if (!T[y] && slack[y] == 0) {
                if (yx[y] == -1) return augment(slackx[y], y);
                T[y] = true;
                if (!S[yx[y]]) q.push_back(yx[y]), add(yx[y], slackx[y]);
            }
        }
    }

    Hungarian(vector<vector<ll>> g)
        : N(g.size()), gain(g), xy(N, -1), yx(N, -1), lx(N, -INF),
        ly(N), slack(N), slackx(N) {
        rep(x, N) rep(y, N) lx[x] = max(lx[x], ly[y]);
        rep(i, N) improve();
    }
};
