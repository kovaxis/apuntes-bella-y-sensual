ll legendre(ll a, ll p) {
    if (a % p == 0) return 0;  if (p == 2) return 1;
    return binexp(a, (p - 1) / 2, p);
}
// sqrt(n) mod p (p must be a prime)
// rnd(a, b) return a random number in [a, b]
ll tonelli_shanks(ll n, ll p) {
    if (n == 0) return 0;
    if (legendre(n, p) != 1) return -1; // no existe
    if (p == 2) return 1;
    ll s = __builtin_ctzll(p - 1);
    ll q = (p - 1LL) >> s, z = rnd(1, p - 1);
    if (s == 1) return binexp(n, (p + 1) / 4LL, p);
    while (legendre(z, p) != p - 1) z = rnd(1, p - 1);
    ll c = binexp(z, q, p), r = binexp(n, (q + 1) / 2, p);
    ll t = binexp(n, q, p), m = s;
    while (t != 1) {
        ll i = 1, ts = (t * t) % p;
        while (ts != 1) i++, ts = (ts * ts) % p;
        ll b = c;
        repx(_, 0, m - i - 1) b = (b * b) % p;
        r = r*b%p; c = b*b%p; t = t*c%p; m = i;
    }
    return r;
}