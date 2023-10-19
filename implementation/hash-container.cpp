namespace{//add (#define tmpl template)(#define ty typename)
  tmpl<ty T> size_t mk_h(const T& v){return hash<T>()(v);}
  void h_cmb(size_t& h, const size_t& v)
  { h ^= v + 0x9e3779b9 + (h << 6) + (h >> 2); }
  tmpl<ty T> struct h_ct{size_t operator()(const T& v)const{
 size_t h=0;for(const auto& e:v){h_cmb(h,mk_h(e));}return h;
  }};
}namespace std{//support for pair<T,U>, vector<T> & map<T,U>
  tmpl<ty T, ty U> struct hash<pair<T, U>>{
    size_t operator()(const pair<T,U>& v) const
 {size_t h=mk_h(v.first);h_cmb(h, mk_h(v.second));return h;}
  };
tmpl<ty... T>struct hash<vector<T...>>:h_ct<vector<T...>>{};
tmpl<ty... T>struct hash<map<T...>>:h_ct<map<T...>>{};   }