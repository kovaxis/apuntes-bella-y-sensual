template <class T>
struct Node {
    T x, lz;
    int l = -1, r = -1;
};

template <class T>
struct Pstl {
    int N;
    vector<Node<T>> a;
    vector<int> head;

    T qneut() { return 0; }
    T merge(T l, T r) { return l + r; }
    T uneut() { return 0; }
    T accum(T u, T x) { return u + x; }
    T apply(T x, T lz, int l, int r) { return x + (r - l) * lz; }

    int build(int vl, int vr) {
        if (vr - vl == 1) a.push_back({qneut(), uneut()}); // node construction
        else {
            int vm = (vl + vr) / 2, l = build(vl, vm), r = build(vm, vr);
            a.push_back({merge(a[l].x, a[r].x), uneut(), l, r}); // query merge
        }
        return a.size() - 1;
    }

    T query(int l, int r, int v, int vl, int vr, T acc) {
        if (l >= vr || r <= vl) return qneut();                    // query neutral
        if (l <= vl && r >= vr) return apply(a[v].x, acc, vl, vr); // update op
        acc = accum(acc, a[v].lz);                                 // update merge
        int vm = (vl + vr) / 2;
        return merge(query(l, r, a[v].l, vl, vm, acc), query(l, r, a[v].r, vm, vr, acc)); // query merge
    }

    int update(int l, int r, T x, int v, int vl, int vr) {
        if (l >= vr || r <= vl || r <= l) return v;
        a.push_back(a[v]);
        v = a.size() - 1;
        if (l <= vl && r >= vr) {
            a[v].x = apply(a[v].x, x, vl, vr); // update op
            a[v].lz = accum(a[v].lz, x);       // update merge
        } else {
            int vm = (vl + vr) / 2;
            a[v].l = update(l, r, x, a[v].l, vl, vm);
            a[v].r = update(l, r, x, a[v].r, vm, vr);
            a[v].x = merge(a[a[v].l].x, a[a[v].r].x); // query merge
        }
        return v;
    }

    Pstl() {}
    Pstl(int N) : N(N) { head.push_back(build(0, N)); }

    T query(int t, int l, int r) {
        return query(l, r, head[t], 0, N, uneut()); // update neutral
    }
    int update(int t, int l, int r, T x) {
        return head.push_back(update(l, r, x, head[t], 0, N)), head.size() - 1;
    }
};