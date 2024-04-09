struct State {int len, link; map<char,int> next; };
State st[2*MAXN]; int sz, last;              // clear next!!
void sa_init(){ last=st[0].len=0; sz=1; st[0].link=-1; }
void sa_extend(char c){// total build O(n log alphabet_size)
    int k = sz++, p; st[k].len = st[last].len + 1;
    for(p=last; p!=-1 && !st[p].next.count(c); p=st[p].link)
        st[p].next[c] = k;
    if(p == -1) st[k].link = 0;
    else {
        int q = st[p].next[c];
        if(st[p].len + 1 == st[q].len) st[k].link = q;
        else {
            int w = sz++; st[w].len = st[p].len + 1;
            st[w].next=st[q].next; st[w].link=st[q].link;
            for(; p!=-1 && st[p].next[c]==q; p=st[p].link)
                st[p].next[c] = w;
            st[q].link=st[k].link = w;
        }
    }
    last = k;
} // # states <= 2n-1 && transitions <= 3n-4 (for n > 2)
// Follow link from `last` to 0, nodes on path are terminal
// # matches = # paths from state to a terminal node
// # substrings = # paths from 0 to any node
// # substrings = sum of (len - len(link)) for all nodes