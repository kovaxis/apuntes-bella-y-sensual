// a * x + b * y == gcd(a, b)
ll ext_gcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) { x = 1, y = 0; return a; }
    ll d = ext_gcd(b, a % b, y, x); y -= a / b * x;return d;
}

// inverse exists if and only if a and M are coprime
// if M is prime: multinv(a, M) = (a**(M-2)) % M
ll multinv(ll a, ll M)
{ ll x, y; ext_gcd(a, M, x, y); return x; }

// all modular inverses from 1 to inv.size()-1
void multinv_all(vector<ll> &inv) {
    inv[1] = 1;
    repx(i, 2, inv.size())
        inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD;
}