struct Node {    // (*) = Optional
	int len;     // length of substring
	int edge[26];// insertion edge for all characters a-z
	int link;    // the Maximum Palindromic Suffix Node for the current Node
	int i;       // (*) start index of current Node
    int cnt = 1; // (*) # of occurrences of this substring
    Node(){ fill(begin(edge), end(edge), -1); }
};
struct EerTree {    // Palindromic Tree
    vector<Node> t; // tree
    int curr;       // current node
    EerTree(string &s) {
        t.resize(2);
        t.reserve(s.size()+2);// (*) max size of tree
        t[0].len = -1;        // root 1
        t[0].link = 0;
        t[1].len = 0;         // root 2
        t[1].link = 0;
        curr = 1;
        rep(i, s.size()) insert(i, s);  // construct tree
        // (*) calculate number of occurrences of each node
        for(int i = t.size()-1; i > 1; i--)
            t[t[i].link].cnt += t[i].cnt;
    }
    void insert(int i, string &s) {
        int tmp = curr;
        while (i - t[tmp].len < 1 || s[i] != s[i-t[tmp].len-1])
            tmp = t[tmp].link;

        if(t[tmp].edge[s[i]-'a'] != -1){
            curr = t[tmp].edge[s[i]-'a'];  // already exists
            t[curr].cnt++;        // (*) increase cnt
            return;
        }
        // create new node
        curr = t[tmp].edge[s[i]-'a'] = t.size(); 
        t.emplace_back();

        t[curr].len = t[tmp].len + 2;    // set length
        t[curr].i = i - t[curr].len + 1;//(*)set start index

        if (t[curr].len == 1) {          // set suffix link    
            t[curr].link = 1;
        } else {
            tmp = t[tmp].link;
            while (i-t[tmp].len < 1 || s[i] != s[i-t[tmp].len-1])
                tmp = t[tmp].link;
            t[curr].link = t[tmp].edge[s[i]-'a'];
        }
    }
};
int main(){
	string s = "abcbab";
    EerTree pt(s);          // construct palindromic tree
	repx(i, 2, pt.t.size()) // list all distinct palindromes
	{
		cout << i-1 << ") ";
		repx(j, pt.t[i].i, pt.t[i].i + pt.t[i].len)
			cout << s[j];
		cout << " " << pt.t[i].cnt << endl;
	}
	return 0;
}
