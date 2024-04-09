// usage:
// Pst<Node<ll>> pst;
// pst = {N};
// int newtime = pst.update(time, index, value);
// Node<ll> result = pst.query(newtime, left, right);

template <class T>
struct Node {
    T x;
    int l = -1, r = -1;

    Node() : x(0) {}
    Node(T x) : x(x) {}
    Node(Node a, Node b, int l = -1, int r = -1) : x(a.x + b.x), l(l), r(r) {}
};

template <class U>
struct Pst {
    int N;
    vector<U> a;
    vector<int> head;

    int build(int vl, int vr) {
        if (vr - vl == 1) a.push_back(U());
        else {
            int vm = (vl + vr) / 2, l = build(vl, vm),
                r = build(vm, vr);
            a.push_back(U(a[l], a[r], l, r));
        }
        return a.size() - 1;
    }

    U query(int l, int r, int v, int vl, int vr) {
        if (l >= vr || r <= vl) return U();
        if (l <= vl && r >= vr) return a[v];
        int vm = (vl + vr) / 2;
        return U(query(l, r, a[v].l, vl, vm),
                 query(l, r, a[v].r, vm, vr));
    }

    int update(int i, U x, int v, int vl, int vr) {
        a.push_back(a[v]);
        v = a.size() - 1;
        if (vr - vl == 1) a[v] = x;
        else {
            int vm = (vl + vr) / 2;
            if (i < vm) a[v].l = update(i, x, a[v].l, vl, vm);
            else a[v].r = update(i, x, a[v].r, vm, vr);
            a[v] = U(a[a[v].l], a[a[v].r], a[v].l, a[v].r);
        }
        return v;
    }

    Pst() {}
    Pst(int N) : N(N) { head.push_back(build(0, N)); }

    U query(int t, int l, int r) {
        return query(l, r, head[t], 0, N);
    }
    int update(int t, int i, U x) {
        return head.push_back(update(i, x, head[t], 0, N)), head.size() - 1;
    }
};