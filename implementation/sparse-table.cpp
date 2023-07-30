#include "../common.h"

// handle immutable range maximum queries (or any idempotent query) in O(1)
template <class T>
struct Sparse {
    vector<vector<T>> st;

    T op(T a, T b) { return max(a, b); }

    Sparse() {}

    void reset(int N) { st = {vector<T>(N)}; }
    void set(int i, T val) { st[0][i] = val; }

    // O(N log N) time
    // O(N log N) memory
    void init() {
        int N = st[0].size();
        int npot = N <= 1 ? 1 : 32 - __builtin_clz(N);
        st.resize(npot);
        repx(i, 1, npot) rep(j, N + 1 - (1 << i)) st[i].push_back(
            op(st[i - 1][j], st[i - 1][j + (1 << (i - 1))])); // query op
    }

    // query maximum in the range [l, r) in O(1) time
    // range must be nonempty!
    T query(int l, int r) {
        int i = 31 - __builtin_clz(r - l);
        return op(st[i][l], st[i][r - (1 << i)]); // query op
    }
};
