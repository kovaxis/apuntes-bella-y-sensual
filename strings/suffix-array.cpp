// build the suffix array
// suffixes are sorted, with each suffix represented by its 
// starting position
vector<int> suffixarray(const string &s) {
    int N = s.size() + 1;//optional: include terminating NUL
    vector<int> p(N), p2(N), c(N), c2(N), cnt(256);
    rep(i, N) cnt[s[i]] += 1;
    repx(b, 1, 256) cnt[b] += cnt[b - 1];
    rep(i, N) p[--cnt[s[i]]] = i;
    repx(i, 1, N) c[p[i]] = c[p[i - 1]] + (s[p[i]] != s[p[i - 1]]);
    for (int k = 1; k < N; k <<= 1) {
        int C = c[p[N - 1]] + 1;
        cnt.assign(C + 1, 0);
        for (int &pi : p) pi = (pi - k + N) % N;
        for (int cl : c) cnt[cl + 1] += 1;
        rep(i, C) cnt[i + 1] += cnt[i];
        rep(i, N) p2[cnt[c[p[i]]]++] = p[i];
        c2[p2[0]] = 0;
        repx(i, 1, N) c2[p2[i]] =
            c2[p2[i - 1]] + (c[p2[i]] != c[p2[i - 1]] ||
                             c[(p2[i] + k) % N] != c[(p2[i - 1] + k) % N]);
        swap(c, c2), swap(p, p2);
    }
    p.erase(p.begin()); // optional: erase terminating NUL
    return p;
}
// build the lcp
// `lcp[i]` represents the length of the longest common
// prefix between suffix i and suffix i+1 in the suffix
//array `p`. the last element of `lcp` is zero by convention
vector<int> makelcp(const string &s, const vector<int> &p) {
    int N = p.size(), k = 0;
    vector<int> r(N), lcp(N);
    rep(i, N) r[p[i]] = i;
    rep(i, N) {
        if (r[i] + 1 >= N) { k = 0; continue; }
        int j = p[r[i] + 1];
        while (i + k < N && j + k < N && s[i + k] == s[j + k]) k += 1;
        lcp[r[i]] = k;
        if (k) k -= 1;
    }
    return lcp;
}
// lexicographically compare the suffixes starting from `i`
// and `j`, considering only up to `K` characters.
// `r` is the inverse suffix array, mapping suffix offsets 
// to indices. requires an LCP sparse table.
int lcp_cmp(vector<int> &r, Sparse<int> &lcp, int i, int j, int K) {
    if (i == j) return 0;
    int ii = r[i], jj = r[j];
    int l = lcp.query(min(ii, jj), max(ii, jj));
    if (l >= K) return 0;
    return ii < jj ? -1 : 1;
}
