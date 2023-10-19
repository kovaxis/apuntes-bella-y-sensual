static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define rnd(a,b) (uniform_int_distribution<ll>(a,b)(rng))

struct Hash {
    size_t operator()(const ll &x) const {
        const uint64_t RAND = chrono::steady_clock::now()
            .time_since_epoch().count();
        uint64_t z = x + RAND + 0x9e3779b97f4a7c15;
        z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
        z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
        return z ^ (z >> 31);
    }
};
template<class T,class U>using umap=unordered_map<T,U,Hash>;
template<class T> using uset = unordered_set<T, Hash>;