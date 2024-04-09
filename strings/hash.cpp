const int K = 2;
struct Hash{
    const ll MOD[K] = {999727999, 1070777777};
    const ll P = 1777771;
    vector<ll> h[K], p[K];
    Hash(string &s){
        int n = s.size();
        rep(k, K){
            h[k].resize(n+1, 0);
            p[k].resize(n+1, 1);
            repx(i, 1, n+1){
                h[k][i] = (h[k][i-1]*P + s[i-1]) % MOD[k];
                p[k][i] = (p[k][i-1]*P) % MOD[k];
            }
        }
    }
    vector<ll> get(int i, int j){
        vector<ll> r(K);
        rep(k, K){
            r[k] = (h[k][j] - h[k][i]*p[k][j-i]) % MOD[k];
            r[k] = (r[k] + MOD[k]) % MOD[k];
        } return r;
    }
};