// Given alphabet [0,k) constructs a cyclic string of length
// k^n that contains every length n string as substr. 
vector<int> deBruijnSeq(int k, int n) { // Recursive FKM 
    if (k == 1) return {0};
    vector<int> seq, aux(n+1); 
    function<void(int,int)> gen = [&](int t, int p) {
        if (t > n) { // +lyndon word of len p
            if (n%p == 0) repx(i,1,p+1) seq.pb(aux[i]); 
        } else {
            aux[t] = aux[t-p]; gen(t+1,p);
            while (++aux[t] < k) gen(t+1,t);
        }
    };
    gen(1,1); return seq;
}