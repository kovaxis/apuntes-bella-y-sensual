#include "../common.h"

// usage:
// St<Node<ll>> st;
// st = {N};
// st.update(index, new_value);
// Node<ll> result = st.query(left, right);

template <class T>
struct Node {
    T x;
    Node() : x(0) {}
    Node(T x) : x(x) {}
    Node(Node a, Node b) : x(a.x + b.x) {}
};

template <class U>
struct St {
    vector<U> a;

    St() {}
    St(int N) : a(4 * N, U()) {} // node neutral

    // query for range [l, r)
    U query(int l, int r, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = a.size() / 4;
        if (l <= vl && r >= vr) return a[v]; // item construction
        int vm = (vl + vr) / 2;
        if (l >= vr || r <= vl) return U();                                   // item neutral
        return U(query(l, r, 2 * v, vl, vm), query(l, r, 2 * v + 1, vm, vr)); // item merge
    }

    // set element i to val
    void update(int i, U val, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = a.size() / 4;
        if (vr - vl == 1) a[v] = val; // item update
        else {
            int vm = (vl + vr) / 2;
            if (i < vm) update(i, val, 2 * v, vl, vm);
            else update(i, val, 2 * v + 1, vm, vr);
            a[v] = U(a[2 * v], a[2 * v + 1]); // node merge
        }
    }
};
