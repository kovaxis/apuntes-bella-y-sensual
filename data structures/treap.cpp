mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
struct item { // to allow duplicates, add random val to keys
    int p, k, n; item *l=0, *r=0;
    item(int k) : p(rng()), k(k), n(1) {}
};
int getn(item *x) { return x ? x->n : 0; }
void recalc(item* x) { if(x) x->n=getn(x->l)+1+getn(x->r); }
void split(item *x, int k, item *&l, item *&r) {
    if (!x) l = r = 0;
    else if (k < x->k) split(x->l, k, l, x->l), r = x;
    else split(x->r, k, x->r, r), l = x;
    recalc(x);
}
void merge(item *&x, item *l, item *r) {
    if (!l || !r) x = l ? l : r;
    else if (l->p > r->p) merge(l->r, l->r, r), x = l;
    else merge(r->l, l, r->l), x = r;
    recalc(x);
}
void insert(item *&x, item *y) {
    if (!x) x = y;
    else if (y->p > x->p) split(x, y->k, y->l, y->r), x = y;
    else insert(y->k < x->k ? x->l : x->r, y);
    recalc(x);
}
void erase(item *&x, int k) {
    if (x->k == k) merge(x, x->l, x->r);
    else erase(k < x->k ? x->l : x->r, k);
    recalc(x);
}