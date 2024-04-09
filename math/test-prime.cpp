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