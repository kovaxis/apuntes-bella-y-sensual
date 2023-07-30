#include "../common.h"

// in-place segment intersection.
void intersect(pair<int, int>& a, pair<int, int> b) {
    a = {max(a.first, b.first), min(a.second, b.second)};
}

// in-place segment "union".
// finds the shortest segment that contains both `a` and `b`.
//
// for [a, b) segments: change > to >= and <= to <
void unite(pair<int, int>& a, pair<int, int> b) {
    if (a.first > a.second)
        a = b;
    else if (b.first <= b.second)
        a = {min(a.first, b.first), max(a.second, b.second)};
}

// segment containment.
//
// [a, b] in [c, d]
// subset or equal: a >= c && b <= d || a >  b
// proper subset:   a >  c && b <  d || a >  b && c <= d
//
// [a, b) in [c, d)
// subset or equal: a >= c && b <= d || a >= b
// proper subset:   a >  c && b <  d || a >= b && c <  d
bool is_subset(pair<int, int> sub, pair<int, int> sup) {
    return sub.first >= sup.first && sub.second <= sup.second ||
           sub.second < sub.first;
}
bool is_subset_proper(pair<int, int> sub, pair<int, int> sup) {
    return sub.first > sup.first && sub.second < sup.second ||
           sub.second < sub.first && sup.first <= sup.second;
}
