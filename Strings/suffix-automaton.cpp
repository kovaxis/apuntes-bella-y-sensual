
#include "../common.h"

struct SuffixAutomaton {
    vector<map<char,int>> edges; // edges[i]  : the labeled edges from node i
    vector<int> link;            // link[i]   : the suffix link of i
    vector<int> length;          // length[i] : the length of the longest string in the ith class
    vector<int> cnt;             // cnt[i]    : number of occurrences of each string in the ith class
    vector<int> paths;           // paths[i]  : number of paths on the automaton starting from i
    vector<bool> terminal;       // terminal[i] : true if i is a terminal state
    vector<int> first_pos;           
    vector<int> last_pos;      
    int last;                    // the index of the equivalence class of the whole string
 
    SuffixAutomaton(string s) {
        edges.push_back(map<char,int>());
        link.push_back(-1);
        length.push_back(0);
        last = 0;
 
        rep(i, s.size()) { // construct r
            edges.push_back(map<char,int>());
            length.push_back(i+1);
            link.push_back(0);
            int r = edges.size() - 1;
            int p = last; // add edges to r and find p with link to q
            while(p >= 0 && !edges[p].count(s[i])) {
                edges[p][s[i]] = r;
                p = link[p];
            }
            if(p != -1) {
                int q = edges[p][s[i]];
                if(length[p] + 1 == length[q]) {
                    link[r] = q; // we do not have to split q, just set the correct suffix link
                } else { // we have to split, add q'
                    edges.push_back(edges[q]); // copy edges of q
                    length.push_back(length[p] + 1);
                    link.push_back(link[q]); // copy parent of q
                    int qq = edges.size()-1;
                    link[q] = qq; // add qq as the new parent of q and r
                    link[r] = qq;
                    while(p >= 0 && edges[p][s[i]] == q) { // move short classes polling to q to poll to q'
                        edges[p][s[i]] = qq;
                        p = link[p];
                    }
                }
            }
            last = r;
        }

    /* ------ Optional ------ */
 
        // mark terminal nodes
        terminal.assign(edges.size(), false);
        int p = last;
        while(p > 0) {
            terminal[p] = true;
            p = link[p];
        }

        // precompute match count
        cnt.assign(edges.size(), -1);
        cnt_matches(0);
 
        // precompute number of paths (substrings) starting from state
        paths.assign(edges.size(), -1);
        cnt_paths(0);

        first_pos.assign(edges.size(), -1);
        get_first_pos(0);

        last_pos.assign(edges.size(), -1);
        get_last_pos(0);
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
        int ans = state == 0 ? 0 : 1;   // without repetition (counts diferent substrings)
    //  int ans = state == 0 ? 0 : cnt[state]; // with repetition
        for(auto edge : edges[state])
            ans += cnt_paths(edge.second);
        return paths[state] = ans;
    }

    int get_first_pos(int state) {
        if(first_pos[state] != -1) return first_pos[state];
        int ans = 0;
        for(auto edge : edges[state])
            ans = max(ans, get_first_pos(edge.second)+1);
        return first_pos[state] = ans;
    }

    int get_last_pos(int state) {
        if(last_pos[state] != -1) return last_pos[state];
        int ans = terminal[state] ? 0 : INT_MAX;//fix
        for(auto edge : edges[state])
            ans = min(ans, get_last_pos(edge.second)+1);
        return last_pos[state] = ans;
    }
 
    string get_k_substring(int k)  // 0-indexed
    {
        string ans;
        int state = 0;
        while(true)
        {
            int curr = state == 0 ? 0 : 1;   // without repetition (counts diferent substrings)
        //  int curr = state == 0 ? 0 : cnt[state]; // with repetition
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