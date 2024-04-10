ii extendedEuclid(ll a, ll b){
    ll x, y; //a*x + b*y = gcd(a,b)
    if (b == 0) return {1, 0};
    auto p = extendedEuclid(b, a%b);
    x = p.second;
    y = p.first - (a/b)*x;
    if(a*x + b*y == -__gcd(a,b)) x=-x, y=-y;
    return {x, y};
}
pair<ii, ii> diophantine(ll a, ll b, ll r){
    //a*x+b*y=r where r is multiple of gcd(a,b);
    ll d = __gcd(a, b);
    a/=d; b/=d; r/=d;
    auto p = extendedEuclid(a, b);
    p.first*=r; p.second*=r;
    assert(a*p.first + b*p.second == r);
    return {p, {-b, a}}; //solutions: p+t*ans.second
}