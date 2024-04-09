struct St {
    ll neut() { return 0; }
    ll merge(ll x, ll y) { return x + y; }

    int n; vector<ll> a;
    St(int n = 0) : n(n), a(2 * n, neut()) {}

    ll query(int l, int r) {
        ll x = neut(), y = neut();
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l & 1) x = merge(x, a[l++]);
            if (r & 1) y = merge(a[--r], y);
        }
        return merge(x, y);
    }

    void update(int i, ll x) {
        for (a[i += n] = x; i /= 2;)
            a[i] = merge(a[2 * i], a[2 * i + 1]);
    }
};