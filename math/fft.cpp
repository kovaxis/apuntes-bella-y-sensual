using cd = complex<double>;
const double PI = acos(-1);
// compute the DFT of a power-of-two-length sequence.
// if `inv` is true, computes the inverse DFT.
void fft(vector<cd> &a, bool inv) {
    int N = a.size(), k = 0, b;
    assert(N == 1 << __builtin_ctz(N));
    repx(i, 1, N) {
        for (b = N >> 1; k & b;) k ^= b, b >>= 1;
        if (i < (k ^= b)) swap(a[i], a[k]);
    }
    for (int l = 2; l <= N; l <<= 1) {
        double ang = 2 * PI / l * (inv ? -1 : 1);
        cd wl(cos(ang), sin(ang));
        for (int i = 0; i < N; i += l) {
            cd w = 1;
            rep(j, l / 2) {
                cd u = a[i + j], v = a[i + j + l / 2] * w;
                a[i + j] = u + v;
                a[i + j + l / 2] = u - v;
                w *= wl;
            }
        }
    }
    if (inv) rep(i, N) a[i] /= N;
}
const ll MOD = 998244353, ROOT = 15311432;
// const ll MOD = 2130706433, ROOT = 1791270792;
// const ll MOD = 9223372036737335297ll, ROOT = 5320774565496356983ll;
void find_root_of_unity(ll M) {
    ll c = M - 1, k = 0;
    while (c % 2 == 0) c /= 2, k += 1;
    // find proper divisors of M - 1
    vector<ll> divs;
    for (ll d = 1; d < c; d++) {
        if (d * d > c) break;
        if (c % d == 0) rep(i, k + 1) divs.push_back(d << i);
    }
    rep(i, k) divs.push_back(c << i);
    // find any primitive root of M
    ll G = -1;
    repx(g, 2, M) {
        bool ok = true;
        for (ll d : divs) ok &= (binexp(g, d, M) != 1);
        if (ok) {
            G = g;
            break;
        }
    }
    assert(G != -1);
    ll w = binexp(G, c, M);
    cerr << "M = c * 2^k + 1" << endl;
    cerr << "  M = " << M << endl;
    cerr << "  c = " << c << endl;
    cerr << "  k = " << k << endl;
    cerr << "  w^(2^k) == 1" << endl;
    cerr << "    w = g^((M-1)/2^k) = g^c" << endl;
    cerr << "    g = " << G << endl;
    cerr << "    w = " << w << endl;
}
// compute the DFT of a power-of-two-length sequence, modulo a special prime
// number with an Nth root of unity, where N is the length of the sequence.
void ntt(vector<ll> &a, bool inv) {
    vector<ll> wn;
    for (ll p = ROOT; p != 1; p = p * p % MOD) wn.push_back(p);
    int N = a.size(), k = 0, b;
    assert(N == 1 << __builtin_ctz(N) && N <= 1 << wn.size());
    rep(i, N) a[i] = (a[i] % MOD + MOD) % MOD;
    repx(i, 1, N) {
        for (b = N >> 1; k & b;) k ^= b, b >>= 1;
        if (i < (k ^= b)) swap(a[i], a[k]);
    }
    for (int l = 2; l <= N; l <<= 1) {
        ll wl = wn[wn.size() - __builtin_ctz(l)];
        if (inv) wl = multinv(wl, MOD);
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
    ll q = multinv(N, MOD);
    if (inv) rep(i, N) a[i] = a[i] * q % MOD;
}
void convolve(vector<cd> &a, vector<cd> b, int n) {
    n = 1 << (32 - __builtin_clz(2 * n - 1));
    a.resize(n), b.resize(n);
    fft(a, false), fft(b, false);
    rep(i, n) a[i] *= b[i];
    fft(a, true);
}