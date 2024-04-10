vector<int> BM(vector<int> x) {
    vector<int> ls, cur;
    int lf, ld;
    rep(i, x.size()) {
        ll t = 0;
        rep(j, cur.size()) t = (t+x[i-j-1]*(ll)cur[j])%MOD;
        if ((t - x[i]) % MOD == 0) continue;
        if (!cur.size()) {
            cur.resize(i + 1); lf = i; ld = (t-x[i]) % MOD;
            continue;
        }
        ll k = -(x[i] - t) * bin_exp(ld, MOD - 2) % MOD;
        vector<int> c(i - lf - 1); c.push_back(k);
        rep(j, ls.size()) c.push_back(-ls[j] * k % MOD);
        if (c.size() < cur.size()) c.resize(cur.size());
        rep(j, cur.size()) c[j] = (c[j] + cur[j]) % MOD;
        if (i - lf + ls.size() >= cur.size()) 
            ls = cur, lf = i, ld = (t - x[i]) % MOD;
        cur = c;
    }
    rep(i, cur.size()) cur[i] = (cur[i] % MOD + MOD) % MOD;
    return cur;
}
// Linear Recurrence
ll MOD = 998244353;
ll LOG = 60;
struct LinearRec{
  typedef vector<int> vi;
  int n; vi terms, trans; vector<vi> bin;
  vi add(vi &a, vi &b){
    vi res(n*2+1);
    rep(i,n+1) rep(j,n+1)
        res[i+j]=(res[i+j]*1LL+(ll)a[i]*b[j])%MOD;
    for(int i=2*n; i>n; --i){
      rep(j,n)
        res[i-1-j]=(res[i-1-j]*1LL+(ll)res[i]*trans[j])%MOD;
      res[i]=0;
    }
    res.erase(res.begin()+n+1,res.end());
    return res;
  }
  LinearRec(vi &terms, vi &trans):terms(terms),trans(trans){
    n=trans.size();vi a(n+1);a[1]=1;
    bin.push_back(a);
    repx(i,1,LOG)bin.push_back(add(bin[i-1],bin[i-1]));
  }
  int calc(ll k){
    vi a(n+1);a[0]=1;
    rep(i,LOG)if((k>>i)&1)a=add(a,bin[i]);
    int ret=0;
    rep(i,n)ret=((ll)ret+(ll)a[i+1]*terms[i])%MOD;
    ret = ret%MOD + MOD;
    return ret%MOD;
  }
};