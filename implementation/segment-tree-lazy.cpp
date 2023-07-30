// 0-based, inclusive-exclusive
// usage:
// Stl3<ll> a;
// a = {N};
template <class T>
struct Stl {
    // immediate, lazy
    vector<pair<T, T>> a;

    T qneutral() { return 0; }
    T merge(T l, T r) { return l + r; }
    T uneutral() { return 0; }
    void update(pair<T, T> &u, T val, int l, int r) { u.first += val * (r - l), u.second += val; }

    Stl() {}
    Stl(int N) : a(4 * N, {qneutral(), uneutral()}) {} // node neutral

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
