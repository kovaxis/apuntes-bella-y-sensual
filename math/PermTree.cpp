struct PermTree {
	vector<int> P; int n; // N = number of nodes in perm tree
	int N = 0, root; vector<vector<int>> child;
	vector<ii> inter, range; vector<int> typ, loc; // inter = index range in perm
	void init(vector<int> _P) {
		P = _P; n = P.size(); Stl L(n); 
		vector<int> mn{-1}, mx{-1}, st;
		rep(i, n){
			if(i) L.update(0, i, -1);
 
			while (mn.back() != -1 && P[mn.back()] > P[i]) {
				int t = mn.back(); mn.pop_back();
				L.update(mn.back()+1,t+1,P[t]);
			}
			L.update(mn.back()+1,i+1,-P[i]); mn.push_back(i); 
			
			while (mx.back() != -1 && P[mx.back()] < P[i]) {
				int t = mx.back(); mx.pop_back();
				L.update(mx.back()+1,t+1,-P[t]);
			}
			L.update(mx.back()+1,i+1,P[i]); mx.push_back(i);
 
			int cur = N++; loc.push_back(cur);
			inter.push_back({i,i}); range.push_back({P[i],P[i]}); typ.push_back(0); child.emplace_back();
			auto add = [](ii a, ii b) -> ii { return {min(a.first, b.first), max(a.second,b.second)};};
			auto adj = [&](int x, int y) { ii a = range[x], b = range[y]; 
				return a.second+1 == b.first || b.second+1 == a.first;};
			while(st.size()){
				if(adj(st.back(), cur)){
					if(child[st.back()].size() && adj(child[st.back()].back(),cur)){
						inter[st.back()] = add(inter[st.back()],inter[cur]);
						range[st.back()] = add(range[st.back()],range[cur]);
						child[st.back()].push_back(cur); cur = st.back(); st.pop_back();
					} else { // make new join node
						int CUR = N++;
						inter.push_back(add(inter[cur],inter[st.back()]));
						range.push_back(add(range[cur],range[st.back()]));
						typ.push_back(range[st.back()] < range[cur] ? 1 : 2);
						child.push_back({st.back(),cur}); cur = CUR; st.pop_back();
					}
					continue;
				}
				if (L.query(0, inter[cur].first) != 0) break;
				int CUR = N++;
				inter.push_back(inter[cur]); range.push_back(range[cur]); typ.push_back(0); child.push_back({cur});
				auto len = [](ii p) { return p.second-p.first;};
				do{
					inter[CUR] = add(inter[CUR],inter[st.back()]);
					range[CUR] = add(range[CUR],range[st.back()]);
					child[CUR].push_back(st.back()); st.pop_back();
				} while (len(inter.back()) != len(range.back()));
				reverse(child[CUR].begin(), child[CUR].end()); cur = CUR;
			}
			st.push_back(cur);
		}
		root = st.back();
	}
};