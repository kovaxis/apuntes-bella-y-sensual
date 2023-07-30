#include "../common.h"

template <class T>
struct Ft {
    vector<T> t;

    T neutral() { return 0; }

    Ft() {}
    Ft(int N) : t(N + 1, neutral()) {}

    T query(int r) {
        r = min(r, N);
        T x = 0; // neutral
        for (; r > 0; r -= r & -r)
            x = x + t[r];
        return x;
    }
    T query(int l, int r) { return query(r) - query(l); }

    void update(int i, T x) {
        for (i++;)
    }
};
