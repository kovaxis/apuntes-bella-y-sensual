// counts the divisors of a positive integer in O(sqrt(n))
ll count_divisors(ll x) {
    ll divs = 1, i = 2;
    for (ll divs = 1, i = 2; x > 1; i++) {
        if (i * i > x) { divs *= 2; break; }
        for (ll d = divs; x % i == 0; x /= i) divs += d;
    }
    return divs;
}
// gets the prime factorization of a number in O(sqrt(n))
vector<pair<ll, int>> factorize(ll x) {
    vector<pair<ll, int>> f;
    for (ll k = 2; x > 1; k++) {
        if (k * k > x) { f.push_back({x, 1}); break; }
        int n = 0;
        while (x % k == 0) x /= k, n++;
        if (n > 0) f.push_back({k, n});
    }
    return f;
}
// iterate over all divisors of a number.
// divisor count upper bound: n^(1.07 / ln ln n)
template <class OP>
void divisors(ll x, OP op) {
    auto facts = factorize(x);
    vector<int> f(facts.size());
    while (true) {
        ll y = 1;
        rep(i, f.size()) rep(j, f[i]) y *= facts[i].first;
        op(y);

        int i;
        for (i = 0; i < f.size(); i++) {
            f[i] += 1;
            if (f[i] <= facts[i].second) break;
            f[i] = 0;
        }
        if (i == f.size()) break;
    }
}
// computes euler totative function phi(x), counting the
// amount of integers in [1, x] that are coprime with x.
// time: O(sqrt(x))
ll phi(ll x) {
    ll phi = 1, k = 2;
    for (; x > 1; k++) {
        if (k * k > x) { phi *= x - 1; break; }
        ll k1 = 1, k0 = 0;
        while (x % k == 0) x /= k, k0 = k1, k1 *= k;
        phi *= k1 - k0;
    }
    return phi;
}
// test-prime.cpp
// change to __int128 if checking numbers over 10^9
bool isprime(ll n) {
    if (n < 2 || n % 6 % 4 != 1) return n - 2 < 2;
    ll A[] = {2,325,9375,28178,450775,9780504,1795265022};
    ll s = __builtin_ctzll(n - 1), d = n >> s;
    for (int a : A) {
        ll p = binexp(a, d, n), i = s;
        while (p != 1 && p != n - 1 && a % n && i--) p = p * p % n;
        if (p != n - 1 && i != s) return 0;
    }
    return 1;
}