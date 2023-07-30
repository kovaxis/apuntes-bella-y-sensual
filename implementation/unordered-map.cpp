#include "../common.h"

// hackproof rng
static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// deterministic rng
uint64_t splitmix64(uint64_t *x) {
    uint64_t z = (*x += 0x9e3779b97f4a7c15);
    z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
    z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
    return z ^ (z >> 31);
}

// hackproof unordered map hash
struct Hash {
    size_t operator()(const ll &x) const {
        static const uint64_t RAND =
            chrono::steady_clock::now().time_since_epoch().count();
        uint64_t z = x + RAND + 0x9e3779b97f4a7c15;
        z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
        z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
        return z ^ (z >> 31);
    }
};

// hackproof unordered_map
template <class T, class U>
using umap = unordered_map<T, U, Hash>;

// hackproof unordered_set
template <class T>
using uset = unordered_set<T, Hash>;

// an unordered map with small integer keys that avoids hashing, but allows O(N)
// iteration and clearing, with N being the amount of items (not the maximum
// key).
template <class T>
struct Map {
    int N;
    vector<bool> used;
    vector<int> keys;
    vector<T> vals;

    Map() : N(0) {}
    // O(C)
    void recap(int C) {
        C += 1, used.resize(C), keys.resize(C), vals.resize(C);
    }

    // O(1)
    T &operator[](int k) {
        if (!used[k]) used[k] = true, keys[N++] = k, vals[k] = T();
        return vals[k];
    }

    // O(N)
    void clear() {
        while (N) used[keys[--N]] = false;
    }

    // O(N)
    template <class OP>
    void iterate(OP op) {
        rep(i, N) op(keys[i], vals[keys[i]]);
    }
};
