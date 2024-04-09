inline int floor_log2(int n)
{ return n <= 1 ? 0 : 31 - __builtin_clz(n); }
inline int ceil_log2(int n)
{ return n <= 1 ? 0 : 32 - __builtin_clz(n - 1); }
inline ll floordiv(ll a, ll b) {return a/b-((a^b)<0&&a%b);}
inline ll ceildiv(ll a, ll b) {return a/b+((a^b)>=0&&a%b);}