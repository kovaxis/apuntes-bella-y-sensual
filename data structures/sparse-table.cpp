template <class T>
struct Sparse {
    T op(T a, T b) { return max(a, b); }

    vector<vector<T>> st;
    Sparse() {}
    Sparse(vector<T> a) : st{a} {
        int N = st[0].size();
        int npot = N <= 1 ? 1 : 32 - __builtin_clz(N);
        st.resize(npot);
        repx(i, 1, npot) rep(j, N + 1 - (1 << i))
        st[i].push_back(
            op(st[i - 1][j], st[i - 1][j + (1 << (i - 1))])
        ); // query op
    }

    T query(int l, int r) { // range must be nonempty!
        int i = 31 - __builtin_clz(r - l);
        return op(st[i][l], st[i][r - (1 << i)]); // queryop
    }
};
