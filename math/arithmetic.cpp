#include "../common.h"

// floor(log2(n)) without precision loss
inline int floor_log2(int n) { return n <= 1 ? 0 : 31 - __builtin_clz(n); }
// ceil(log2(n)) without precision loss
inline int ceil_log2(int n) { return n <= 1 ? 0 : 32 - __builtin_clz(n - 1); }

inline ll floordiv(ll a, ll b) {
    return a / b - ((a ^ b) < 0 && a % b);
}

inline ll ceildiv(ll a, ll b) {
    return a / b + ((a ^ b) >= 0 && a % b);
}

// a^e through binary exponentiation.
ll binexp(ll a, ll e) {
    ll res = 1; // neutral element
    while (e) {
        if (e & 1) res = res * a; // multiplication
        a = a * a;                // multiplication
        e >>= 1;
    }
    return res;
}
