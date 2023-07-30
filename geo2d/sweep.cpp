#include "point.cpp"

// iterate over all pairs of points
// `op` is called with all ordered pairs of different indices `(i, j)`
// additionally, the `ps` vector is kept sorted by signed distance
// to the line formed by `i` and `j`
// for example, if the vector from `i` to `j` is pointing right,
// the `ps` vector is sorted from smallest `y` to largest `y`
// note that, because the `ps` vector is sorted by signed distance,
// `j` is always equal to `i + 1`
// this means that the amount of points to the left of the line is always `N - i`
template <class OP>
void all_pair_points(vector<P> &ps, OP op) {
    int N = ps.size();
    sort(ps.begin(), ps.end(), [](P a, P b) {
        return make_pair(a.y, a.x) < make_pair(b.y, b.x);
    });
    vector<pair<int, int>> ss;
    rep(i, N) rep(j, N) if (i != j) ss.push_back({i, j});
    stable_sort(ss.begin(), ss.end(), [&](auto a, auto b) {
        return (ps[a.second] - ps[a.first]).angle_lt(ps[b.second] - ps[b.first]);
    });
    vector<int> p(N); rep(i, N) p[i] = i;
    for (auto [i, j] : ss)
        { op(p[i], p[j]); swap(ps[p[i]], ps[p[j]]); swap(p[i], p[j]); }
}
