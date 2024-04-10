struct Node {    // (*) = Optional
    int len;     // length of substring
    int to[26];  // insertion edge for all characters a-z
    int link;    // maximun palindromic suffix
    int i;       // (*) start index of current Node
    int cnt;     // (*) # of occurrences of this substring
    Node(int len, int link=0, int i=0, int cnt=1): len(len),
    link(link), i(i), cnt(cnt) {memset(to, 0, sizeof(to));}
}; struct EerTree {    // Palindromic Tree
    vector<Node> t; // tree (max size of tree is n+2)
    int last;       // current node
    EerTree(string &s) : last(0) {
        t.emplace_back(-1); t.emplace_back(0); // root 1 & 2
        rep(i, s.size()) add(i, s);  // construct tree
        for(int i = t.size()-1; i > 1; i--) 
            t[t[i].link].cnt += t[i].cnt;
    }
    void add(int i, string &s){         // vangrind warning:
        int p=last, c=s[i]-'a';         // i-t[p].len-1 = -1
        while(s[i-t[p].len-1] != s[i]) p = t[p].link;
        if(t[p].to[c]){ last = t[p].to[c]; t[last].cnt++; }
        else{
            int q = t[p].link;
            while(s[i-t[q].len-1] != s[i]) q = t[q].link;
            q = max(1, t[q].to[c]);
            last = t[p].to[c] = t.size();
            t.emplace_back(t[p].len + 2, q, i-t[p].len-1);
        }
    }
};
void main(){
    string s = "abcbab"; EerTree pt(s); // build EerTree
    repx(i, 2, pt.t.size()){// list all distinct palindromes
        repx(j,pt.t[i].i,pt.t[i].i+pt.t[i].len)cout << s[j];
        cout << " " << pt.t[i].cnt << endl;
    }
}