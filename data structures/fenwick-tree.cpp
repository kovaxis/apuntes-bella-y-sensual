int ft[MAXN+1]; // add dimension for multi-d
void upd(int i0, int v){ // add v to i0th element
    for(int i=i0+1;i<=MAXN;i+=i&-i)ft[i]+=v;//+ fors
}
int get(int i0){ // get sum of range [0,i0)
    int r=0; // add fors
    for(int i=i0;i;i-=i&-i)r+=ft[i];
    return r;
}
int get_sum(int i0,int i1){//sum of [i0,i1)
    return get(i1)-get(i0);
}