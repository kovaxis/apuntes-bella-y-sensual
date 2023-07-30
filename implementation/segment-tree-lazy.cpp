#include "../common.h"

// 0-based, inclusive-exclusive
// usage:
// Stl3<ll> a;
// a = {N};
template <class T>
struct Stl3 {
    // immediate, lazy
    vector<pair<T, T>> a;

    T qneutral() { return 0; }
    T merge(T l, T r) { return l + r; }
    T uneutral() { return 0; }
    void update(pair<T, T> &u, T val, int l, int r) { u.first += val * (r - l), u.second += val; }

    Stl3() {}
    Stl3(int N) : a(4 * N, {qneutral(), uneutral()}) {} // node neutral

    void push(int v, int vl, int vm, int vr) {
        update(a[2 * v], a[v].second, vl, vm);     // node update
        update(a[2 * v + 1], a[v].second, vm, vr); // node update
        a[v].second = uneutral();                  // update neutral
    }

    // query for range [l, r)
    T query(int l, int r, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = a.size() / 4;
        if (l <= vl && r >= vr) return a[v].first; // query op
        if (l >= vr || r <= vl) return qneutral(); // query neutral
        int vm = (vl + vr) / 2;
        push(v, vl, vm, vr);
        return merge(query(l, r, 2 * v, vl, vm), query(l, r, 2 * v + 1, vm, vr)); // item merge
    }

    // update range [l, r) using val
    void update(int l, int r, T val, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = a.size() / 4;
        if (l >= vr || r <= vl || r <= l) return;
        if (l <= vl && r >= vr) update(a[v], val, vl, vr); // node update
        else {
            int vm = (vl + vr) / 2;
            push(v, vl, vm, vr);
            update(l, r, val, 2 * v, vl, vm);
            update(l, r, val, 2 * v + 1, vm, vr);
            a[v].first = merge(a[2 * v].first, a[2 * v + 1].first); // node merge
        }
    }
};

struct Node {
    ll x, lazy;

    Node() : x(neutral()), lazy(0) {} // query neutral, update neutral
    Node(ll x_) : Node() { x = x_; }
    Node(Node &l, Node &r) : Node() { refresh(l, r); }      // node merge construction
    void refresh(Node &l, Node &r) { x = merge(l.x, r.x); } // node merge

    void update(ll val, int l, int r) { x += val * (r - l), lazy += val; } // update-query, update accumulate
    ll take() {
        ll z = 0; // update neutral
        swap(lazy, z);
        return z;
    }

    ll query() { return x; }
    static ll neutral() { return 0; }             // query neutral
    static ll merge(ll l, ll r) { return l + r; } // query merge
};

template <class T, class Node>
struct Stl {
    vector<Node> node;

    void reset(int N) { node.assign(4 * N, {}); } // node neutral

    void build(const vector<T> &a, int v = 1, int vl = 0, int vr = -1) {
        node.resize(4 * a.size()), vr = vr == -1 ? node.size() / 4 : vr;
        if (vr - vl == 1) {
            node[v] = {a[vl]}; // node construction
            return;
        }
        int vm = (vl + vr) / 2;
        build(a, 2 * v, vl, vm);
        build(a, 2 * v + 1, vm, vr);
        node[v] = {node[2 * v], node[2 * v + 1]}; // node merge construction
    }

    void push(int v, int vl, int vm, int vr) {
        T lazy = node[v].take();              // update neutral
        node[2 * v].update(lazy, vl, vm);     // node update
        node[2 * v + 1].update(lazy, vm, vr); // node update
    }

    // query for range [l, r)
    T query(int l, int r, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = node.size() / 4;
        if (l <= vl && r >= vr) return node[v].query(); // query op
        if (l >= vr || r <= vl) return Node::neutral(); // query neutral
        int vm = (vl + vr) / 2;
        push(v, vl, vm, vr);
        return Node::merge(query(l, r, 2 * v, vl, vm), query(l, r, 2 * v + 1, vm, vr)); // item merge
    }

    // update range [l, r) using val
    void update(int l, int r, T val, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = node.size() / 4;
        if (l >= vr || r <= vl || r <= l) return;
        if (l <= vl && r >= vr) node[v].update(val, vl, vr); // node update
        else {
            int vm = (vl + vr) / 2;
            push(v, vl, vm, vr);
            update(l, r, val, 2 * v, vl, vm);
            update(l, r, val, 2 * v + 1, vm, vr);
            node[v].refresh(node[2 * v], node[2 * v + 1]); // node merge
        }
    }
};
