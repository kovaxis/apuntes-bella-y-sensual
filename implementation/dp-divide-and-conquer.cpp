// for every index i assign an optimal index j, such that
// cost(i, j) is minimal for every i. the property that if 
// i2 >= i1 then j2 >= j1 is exploited (monotonic condition)
// calculate optimal index for all indices in range [l, r)
// knowing that the optimal index for every index in this 
// range is within [optl, optr).
// time: O(N log N)
void calc(vector<int> &opt, int l, int r,int optl,int optr){
    if (l == r) return;
    int i = (l + r) / 2;
    ll optc = INF;
    int optj;
    repx(j, optl, optr) {
        ll c = i + j; // cost(i, j)
        if (c < optc) optc = c, optj = j;
    }
    opt[i] = optj;
    calc(opt, l, i, optl, optj + 1);
    calc(opt, i + 1, r, optj, optr);
}