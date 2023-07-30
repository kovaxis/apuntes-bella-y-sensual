#include "common.h"

// search x in a[i]
//
// first a[i] >  x:   upper_bound(a, x)
// first a[i] >= x:   lower_bound(a, x)
//  last a[i] <  x: --lower_bound(a, x)
//  last a[i] <= x: --upper_bound(a, x)

// note: searching for the largest [l, r] such that f(l) > a & f(r) < b where
// [a, b] is a range in f() space may result in negative [l, r] ranges.

// searches for a value in an [l, r] range (both inclusive).
//
// the `isleft(m)` function evaluates whether `m` is strictly to the left of the
// target value.
int binsearch_left(int l, int r, bool isleft(int)) {
    while (l != r) {
        int m = (l + r) / 2;
        if (isleft(m)) {
            l = m + 1;
        } else {
            r = m;
        }
    }
    return l;
}

// searches for a value in an [l, r] range (both inclusive).
//
// the `isright(m)` function evaluates whether `m` is strictly to the right of
// the target value.
//
// note the `+1` when computing `m`, which avoids infinite loops.
// the only difference with `binsearch_left` is how the evaluation function is
// specified. both are functionally identical.
int binsearch_right(int l, int r, bool isright(int)) {
    while (l != r) {
        int m = (l + r + 1) / 2;
        if (isright(m)) {
            r = m - 1;
        } else {
            l = m;
        }
    }
    return l;
}

// continuous ternary (golden section) search.
//
// searches for a minimum value of the given unimodal function (monotonic
// positive derivative).
template <typename T, typename U>
pair<T, U> ctersearch(int iter, T l, T r, U f(T)) {
    const T INVG = 0.61803398874989484820;

    T m = l + (r - l) * INVG;
    U lv = f(l), rv = f(r), mv = f(m);
    rep(i, iter) {
        T x = l + (m - l) * INVG;
        U xv = f(x);
        if (xv > mv) l = r, lv = rv, r = x, rv = xv;
        else r = m, rv = mv, m = x, mv = xv;
    }
    return {m, mv};
}
