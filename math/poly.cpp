
#include "../common.h"

#define NOMAIN_MOD
#include "mod.cpp"

using cd = complex<double>;
const double PI = acos(-1);

// compute the DFT of a power-of-two-length sequence.
// if `inv` is true, computes the inverse DFT.
//
// the DFT of a polynomial A(x) = A0 + A1*x + A2*x^2 + ... + An*x^n is the array
// of the polynomial A evaluated in all nths roots of unity: [A(w0), A(w1),
// A(w2), ..., A(wn-1)], where w0 = 1 and w1 is the nth principal root of unity.
void fft(vector<cd> &a, bool inv) {
    int N = a.size(), k = 0;
    assert(N == 1 << __builtin_ctz(N));

    rep(i, N) {
        int b = N >> 1;
        while (k & b) k ^= b, b >>= 1;
        k ^= b;
        if (i < k) swap(a[i], a[k]);
    }

    for (int l = 2; l <= N; l <<= 1) {
        double ang = 2 * PI / l * (inv ? -1 : 1);
        cd wl(cos(ang), sin(ang));
        for (int i = 0; i < N; i += l) {
            cd w(1);
            repx(j, 0, l / 2) {
                cd u = a[i + j], v = a[i + j + l / 2] * w;
                a[i + j] = u + v;
                a[i + j + l / 2] = u - v;
                w *= wl;
            }
        }
    }

    if (inv)
        for (cd &x : a) x /= N;
}

const ll MOD = 7340033, ROOT = 5, ROOTPOW = 1 << 20;

void find_root_of_unity(ll M) {
    ll c = M - 1, k = 0;
    while (c % 2 == 0) c /= 2, k += 1;

    // find proper divisors of M - 1
    vector<int> divs;
    repx(d, 1, c) {
        if (d * d > c) break;
        if (c % d == 0) rep(i, k + 1) divs.push_back(d << i);
    }
    rep(i, k) divs.push_back(c << i);

    // find any primitive root of M
    ll G = -1;
    repx(g, 2, M) {
        bool ok = true;
        for (int d : divs) ok &= (binexp(g, d, M) != 1);
        if (ok) {
            G = g;
            break;
        }
    }
    assert(G != -1);

    ll w = binexp(G, c, M);
    cerr << M << " = c * 2^k + 1" << endl;
    cerr << "  c = " << c << endl;
    cerr << "  k = " << k << endl;
    cerr << "w^(2^k) == 1" << endl;
    cerr << "  w = " << w << endl;
}

// compute the DFT of a power-of-two-length sequence, modulo a special prime
// number with principal root.
//
// the modulus _must_ be a prime number with an Nth root of unity, where N is a
// power of two. the FFT can only be performed on arrays of size <= N.
void ntt(vector<ll> &a, bool inv) {
    int N = a.size(), k = 0;
    assert(N == 1 << __builtin_ctz(N) && N <= ROOTPOW);
    rep(i, N) a[i] = (a[i] % MOD + MOD) % MOD;

    repx(i, 1, N) {
        int b = N >> 1;
        while (k & b) k ^= b, b >>= 1;
        k ^= b;
        if (i < k) swap(a[i], a[k]);
    }

    for (int l = 2; l <= N; l <<= 1) {
        ll wl = inv ? multinv(ROOT, MOD) : ROOT;
        for (ll i = ROOTPOW; i > l; i >>= 1) wl = wl * wl % MOD;
        for (int i = 0; i < N; i += l) {
            ll w = 1;
            repx(j, 0, l / 2) {
                ll u = a[i + j], v = a[i + j + l / 2] * w % MOD;
                a[i + j] = (u + v) % MOD;
                a[i + j + l / 2] = (u - v + MOD) % MOD;
                w = w * wl % MOD;
            }
        }
    }

    ll ninv = multinv(N, MOD);
    if (inv)
        for (ll &x : a) x = x * ninv % MOD;
}

void convolve(vector<ll> &a, vector<ll> b, int n) {
    n = 1 << (32 - __builtin_clz(2 * n - 1));
    a.resize(n), b.resize(n);
    ntt(a, false), ntt(b, false);
    rep(i, n) a[i] *= b[i];
    ntt(a, true), ntt(b, true);
}

using T = ll;
T pmul(T a, T b) { return a * b % MOD; }
T padd(T a, T b) { return (a + b) % MOD; }
T psub(T a, T b) { return (a - b + MOD) % MOD; }
T pinv(T a) { return multinv(a, MOD); }

struct Poly {
    vector<T> a;

    Poly() {}
    Poly(T c) : a(c) { trim(); }
    Poly(vector<T> c) : a(c) { trim(); }

    void trim() {
        while (!a.empty() && a.back() == 0) a.pop_back();
    }
    int deg() const { return a.empty() ? -1000000 : a.size() - 1; }
    Poly sub(int l, int r) const {
        r = min(r, (int)a.size()), l = min(l, r);
        return vector<T>(a.begin() + l, a.begin() + r);
    }
    Poly trunc(int n) const { return sub(0, n); }
    Poly shl(int n) const {
        Poly out = *this;
        out.a.insert(out.a.begin(), n, 0);
        return out;
    }
    Poly rev(int n, bool r = false) const {
        Poly out(*this);
        if (r) out.a.resize(max(n, (int)a.size()));
        reverse(out.a.begin(), out.a.end());
        return out.trunc(n);
    }

    Poly &operator+=(const Poly &rhs) {
        auto &b = rhs.a;
        a.resize(max(a.size(), b.size()));
        rep(i, b.size()) a[i] = padd(a[i], b[i]); // add
        trim();
        return *this;
    }
    Poly &operator-=(const Poly &rhs) {
        auto &b = rhs.a;
        a.resize(max(a.size(), b.size()));
        rep(i, b.size()) a[i] = psub(a[i], b[i]); // sub
        trim();
        return *this;
    }
    Poly &operator*=(const Poly &rhs) {
        int n = deg() + rhs.deg() + 1;
        if (n <= 0) return *this = Poly();
        n = 1 << (n <= 1 ? 0 : 32 - __builtin_clz(n - 1));
        vector<T> b = rhs.a;
        a.resize(n), b.resize(n);
        ntt(a, false), ntt(b, false);             // fft
        rep(i, a.size()) a[i] = pmul(a[i], b[i]); // mul
        ntt(a, true), trim();                     // invfft
        return *this;
    }
    Poly inv(int n) const {
        assert(deg() >= 0);
        Poly ans = pinv(a[0]); // inverse
        int b = 1;
        while (b < n) {
            Poly C = (ans * trunc(2 * b)).sub(b, 2 * b);
            ans -= (ans * C).trunc(b).shl(b);
            b *= 2;
        }
        return ans.trunc(n);
    }

    Poly operator+(const Poly &rhs) const { return Poly(*this) += rhs; }
    Poly operator-(const Poly &rhs) const { return Poly(*this) -= rhs; }
    Poly operator*(const Poly &rhs) const { return Poly(*this) *= rhs; }

    pair<Poly, Poly> divmod(const Poly &b) const {
        if (deg() < b.deg()) return {Poly(), *this};
        int d = deg() - b.deg() + 1;
        Poly D = (rev(d) * b.rev(d).inv(d)).trunc(d).rev(d, true);
        return {D, *this - D * b};
    }
    Poly operator/(const Poly &b) const { return divmod(b).first; }
    Poly operator%(const Poly &b) const { return divmod(b).second; }
    Poly &operator/=(const Poly &b) { return *this = divmod(b).first; }
    Poly &operator%=(const Poly &b) { return *this = divmod(b).second; }

    T eval(T x) {
        T y = 0;
        invrep(i, a.size()) y = padd(pmul(y, x), a[i]); // add, mul
        return y;
    }
    Poly &build(vector<Poly> &tree, vector<T> &x, int v, int l, int r) {
        if (l == r) return tree[v] = vector<T>{-x[l], 1};
        int m = (l + r) / 2;
        return tree[v] = build(tree, x, 2 * v, l, m) *
                         build(tree, x, 2 * v + 1, m + 1, r);
    }
    void subeval(vector<Poly> &tree, vector<T> &x, vector<T> &y, int v, int l,
                 int r) {
        if (l == r) {
            y[l] = eval(x[l]);
            return;
        }
        int m = (l + r) / 2;
        (*this % tree[2 * v]).subeval(tree, x, y, 2 * v, l, m);
        (*this % tree[2 * v + 1]).subeval(tree, x, y, 2 * v + 1, m + 1, r);
    }
    // evaluate m points in O(k (log k)^2) with k = max(n, m).
    vector<T> multieval(vector<T> &x) {
        int N = x.size();
        if (deg() < 0) return vector<T>(N, 0);
        vector<Poly> tree(4 * N);
        build(tree, x, 1, 0, N - 1);
        vector<T> y(N);
        subeval(tree, x, y, 1, 0, N - 1);
        return y;
    }

    friend ostream &operator<<(ostream &s, const Poly &p) {
        s << "(";
        bool first = true;
        rep(i, p.a.size()) {
            if (p.a[i] == 0) continue;
            if (!first) s << " + ";
            s << p.a[i];
            if (i > 0) s << " x";
            if (i > 1) s << "^" << i;
            first = false;
        }
        s << ")";
        return s;
    }
};

#ifndef NOMAIN_POLY

int main() {
    Poly p1({1, 4});
    Poly p2({-3, 2});
    Poly p3({12, 12, 12, 1});
    Poly p4({128, 40, 29, 2, 0});

    cout << p1 << " * " << p2 << " = " << p1 * p2 << endl;

    vector<ll> xs = {-4, -3, -2, -1, 0, 1, 2, 3, 4};
    for (ll &x : xs) x = (x % MOD + MOD) % MOD;
    vector<ll> ys = p2.multieval(xs);
    cout << "P(x) = " << p2 << endl;
    cout << "x -> P(x):" << endl;
    rep(i, xs.size()) { cout << "  " << xs[i] << " -> " << ys[i] << endl; }

    cerr << endl;
    find_root_of_unity(7340033);

    cerr << endl;
    find_root_of_unity(998244353);
}

#endif
