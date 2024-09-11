// O(N * F) (F = max flow)
vector<pair<ii,ll>> gomoryHu(int N, vector<pair<ii,ll>>&ed){ 
	vector<int> par(N); Dinic D(N, 0, 0);
    for(auto [e, w]: ed){
        auto [u, v] = e;
        D.G[u].push_back(D.E.size());D.E.push_back({u,v,w});
        D.G[v].push_back(D.E.size());D.E.push_back({v,u,w});
    }
	vector<pair<ii,ll>> ans;
	repx(i,1,N){
        for(int j = 0; j<int(D.E.size()); j = j + 2){
            D.E[j].c = D.E[j^1].c= ((D.E[j].c - D.E[j].f)
                + (D.E[j^1].c - D.E[j^1].f)) / 2;
            D.E[j].f = D.E[j^1].f = 0;
        }
        D.s = i; D.t = par[i];
        ans.push_back({{i, par[i]}, D.maxflow()});
		repx(j,i+1,N)
            if (par[j] == par[i] && D.lvl[j] >= 0) par[j]=i;
	}
	return ans;
}