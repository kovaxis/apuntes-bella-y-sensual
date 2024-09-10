//O(G*I^{1.5}) calls to oracle
//G ground set, I independent set
//MatroidIsect<Gmat,Cmat> M(ed.size(),Gmat(ed),Cmat(col));

struct Gmat { // graphic matroid
	int V = 0; vector<ii> ed; Dsu D;
	Gmat(vector<ii> _ed):ed(_ed){
		map<int,int> m; for(auto &t: ed) m[t.first] = m[t.second] = 0;
		for(auto &t: m) t.second = V++; 
		for(auto &t: ed) t.first = m[t.first], t.second = m[t.second];
	}
	void clear() { D.p = vector<int>(V, -1); }
	void ins(int i) { D.unite(ed[i].first, ed[i].second); }
	bool indep(int i) { return !D.sameSet(ed[i].first, ed[i].second); }
};

struct Cmat { // colorful matroid
	int C = 0; vector<int> col; vector<bool> used;
	Cmat(vector<int> col):col(col) {for(auto &t: col) C = max(C, t+1);}
	void clear() { used.assign(C, 0); }
	void ins(int i) { used[col[i]] = 1; }
	bool indep(int i) { return !used[col[i]]; }
};
template<class M1, class M2> struct MatroidIsect {
	int n; vector<bool> iset; M1 m1; M2 m2;
	bool augment() {
		vector<int> pre(n+1,-1); queue<int> q({n});
		while(q.size()){
			int x = q.front(); q.pop();
			if (iset[x]) {
				m1.clear(); rep(i,n) if (iset[i] && i != x) m1.ins(i);
				rep(i,n) if (!iset[i] && pre[i] == -1 && m1.indep(i))
					pre[i] = x, q.push(i);
			} else {
				auto backE = [&]() { // back edge
					m2.clear(); 
					rep(c,2)rep(i,n)if((x==i||iset[i])&&(pre[i]==-1)==c){
						if (!m2.indep(i))return c?pre[i]=x,q.push(i),i:-1;
						m2.ins(i); }
					return n; 
				};
				for (int y; (y = backE()) != -1;) if (y == n) { 
					for(; x != n; x = pre[x]) iset[x] = !iset[x];
					return 1; }
			}
		}
		return 0;
	}
	MatroidIsect(int n, M1 m1, M2 m2):n(n), m1(m1), m2(m2) {
		iset.assign(n+1,0); iset[n] = 1;
		m1.clear(); m2.clear(); // greedily add to basis
		invrep(i,n) if (m1.indep(i) && m2.indep(i)) 
			iset[i] = 1, m1.ins(i), m2.ins(i); 
		while (augment());
	}
};