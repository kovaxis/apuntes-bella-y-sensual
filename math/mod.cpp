#include "../common.h"

ll binexp(ll a, ll e, ll M) {
    assert(e >= 0);
    ll res = 1 % M;
    while (e) {
        if (e & 1) res = res * a % M;
        a = a * a % M;
        e >>= 1;
    }
    return res;
}

ll multinv(ll a, ll M) { return binexp(a, M - 2, M); }

// calculate gcd(a, b).
// also, calculate x and y such that:
// a * x + b * y == gcd(a, b)
//
// time: O(log min(a, b))
// (ignoring complexity of arithmetic)
ll ext_gcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    ll d = ext_gcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

// compute inverse with any M.
// a and M must be coprime for inverse to exist!
ll multinv_euc(ll a, ll M) {
    ll x, y;
    ext_gcd(a, M, x, y);
    return x;
}

// multiply two big numbers (~10^18) under a large modulo, without resorting to
// bigints.
ll bigmul(ll x, ll y, ll M) {
    ll z = 0;
    while (y) {
        if (y & 1) z = (z + x) % M;
        x = (x << 1) % M, y >>= 1;
    }
    return z;
}

struct Mod {
    int a;
    static const int M = 1e9 + 7;

    Mod(ll aa) : a((aa % M + M) % M) {}

    Mod operator+(Mod rhs) const { return (a + rhs.a) % M; }
    Mod operator-(Mod rhs) const { return (a - rhs.a + M) % M; }
    Mod operator-() const { return Mod(0) - *this; }
    Mod operator*(Mod rhs) const { return (ll)a * rhs.a % M; }

    Mod operator+=(Mod rhs) { return *this = *this + rhs; }
    Mod operator-=(Mod rhs) { return *this = *this - rhs; }
    Mod operator*=(Mod rhs) { return *this = *this * rhs; }

    Mod bigmul(ll big) const { return ::bigmul(a, big, M); }

    Mod binexp(ll e) const { return ::binexp(a, e, M); }
    // Mod multinv() const { return ::multinv(a, M); } // prime M
    Mod multinv() const { return ::multinv_euc(a, M); } // possibly composite M
};

// dynamic modulus
struct DMod {
    int a, M;

    DMod(ll aa, ll m) : M(m), a((aa % m + m) % m) {}

    DMod operator+(DMod rhs) const { return {(a + rhs.a) % M, M}; }
    DMod operator-(DMod rhs) const { return {(a - rhs.a + M) % M, M}; }
    DMod operator-() const { return DMod(0, M) - *this; }
    DMod operator*(DMod rhs) const { return {(ll)a * rhs.a % M, M}; }

    DMod operator+=(DMod rhs) { return *this = *this + rhs; }
    DMod operator-=(DMod rhs) { return *this = *this - rhs; }
    DMod operator*=(DMod rhs) { return *this = *this * rhs; }

    DMod bigmul(ll big) const { return {::bigmul(a, big, M), M}; }

    DMod binexp(ll e) const { return {::binexp(a, e, M), M}; }
    DMod multinv() const { return {::multinv(a, M), M}; } // prime M
    // DMod multinv() const { return {::multinv_euc(a, M), M}; } // possibly composite M
};
