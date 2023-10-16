struct SuffixAutomaton {
    vector<map<char,int>> edges;
    vector<int> link, len, cnt, paths, pos;           
    vector<bool> terminal;
    int last;  // idx of the eq. class of the whole string
    SuffixAutomaton(string s) :last(0) {
        edges.push_back({});
        link.push_back(-1);
        len.push_back(0);
        rep(i, s.size()) {
            edges.push_back({});
            len.push_back(i+1);
            link.push_back(0);
            int r = len.size() - 1, p = last;
            while(p >= 0 && !edges[p].count(s[i])) {
                edges[p][s[i]] = r;
                p = link[p];
            }
            if(p != -1) {
                int q = edges[p][s[i]];
                if(len[p] + 1 == len[q]) link[r] = q; 
                else {
                    edges.push_back(edges[q]); 
                    len.push_back(len[p] + 1);
                    link.push_back(link[q]); 
                    int qq= link[q] = link[r] =len.size()-1;
                    while(p >= 0 && edges[p][s[i]] == q){ 
                        edges[p][s[i]] = qq;
                        p = link[p];
                    }
                }
            }
            last = r;
        } /* ------ Optional ------ */
        terminal.assign(len.size(), 0);
        for(int p = last; p > 0; p = link[p]) terminal[p]=1;
        cnt.assign(len.size(), -1); cnt_matches(0);
        //precompute # of paths (substr) starting from state
        paths.assign(len.size(), -1); cnt_paths(0);
        pos.assign(len.size(), -1); get_pos(0);
    }
    int cnt_matches(int state) {
        if(cnt[state] != -1) return cnt[state];
        int ans = terminal[state];
        for(auto edge : edges[state])
            ans += cnt_matches(edge.second);
        return cnt[state] = ans;
    }
    int cnt_paths(int state) {
        if(paths[state] != -1) return paths[state];
        int ans = state != 0;         // without repetitions
    //  int ans = state == 0 ? 0 : cnt[state];  // with rep.
        for(auto edge : edges[state])
            ans += cnt_paths(edge.second);
        return paths[state] = ans;
    }
    int get_pos(int state) { // gets first pos
        if(pos[state] != -1) return pos[state];
        int ans = 0;       		           // max->first_pos 
	//	int ans = terminal[state] ? 0 : 1e9;// min->last_pos
        for(auto edge : edges[state])
            ans = max(ans, get_pos(edge.second)+1); //or min
        return pos[state] = ans;
    }
    string get_k_substring(int k) { // 0-indexed
        string ans; int state = 0;
        while(1){
            int curr = state != 0;     // without repetition 
        //  int curr = state == 0 ? 0 : cnt[state]; // with
            if(curr > k) return ans;
            k -= curr;
            for(auto edge : edges[state]) {
                if(paths[edge.second] <= k) {
                    k -= paths[edge.second];
                } else {
                    ans += edge.first;
                    state = edge.second;
                    break;
                }
            }
        }
    }
};