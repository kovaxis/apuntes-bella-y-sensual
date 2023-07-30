
#include "../common.h"

// compute substring hashes in O(1).
// hashes are compatible between different strings.
struct Hash {
    ll HMOD;
    int N;
    vector<int> h;
    vector<int> p;

    Hash() {}
    // O(N)
    Hash(const string& s, ll HMOD_ = 1000003931)
        : N(s.size() + 1), HMOD(HMOD_), p(N), h(N) {
        static const ll P =
            chrono::steady_clock::now().time_since_epoch().count() % (1 << 29);
        p[0] = 1;
        rep(i, N - 1) p[i + 1] = p[i] * P % HMOD;
        rep(i, N - 1) h[i + 1] = (h[i] + (ll)s[i] * p[i]) % HMOD;
    }

    // O(1)
    pair<ll, int> get(int i, int j) { return {(h[j] - h[i] + HMOD) % HMOD, i}; }

    bool cmp(pair<ll, int> x0, pair<ll, int> x1) {
        int d = x0.second - x1.second;
        ll& lo = d < 0 ? x0.first : x1.first;
        lo = lo * p[abs(d)] % HMOD;
        return x0.first == x1.first;
    }
};

// compute hashes in multiple prime modulos simultaneously, to reduce the chance
// of collisions.
struct HashM {
    int N;
    vector<Hash> sub;

    HashM() {}
    // O(K N)
    HashM(const string& s, const vector<ll>& mods) : N(mods.size()), sub(N) {
        rep(i, N) sub[i] = Hash(s, mods[i]);
    }

    // O(K)
    vector<pair<ll, int>> get(int i, int j) {
        vector<pair<ll, int>> hs(N);
        rep(k, N) hs[k] = sub[k].get(i, j);
        return hs;
    }

    bool cmp(const vector<pair<ll, int>>& x0, const vector<pair<ll, int>>& x1) {
        rep(i, N) if (!sub[i].cmp(x0[i], x1[i])) return false;
        return true;
    }

    bool cmp(int i0, int j0, int i1, int j1) {
        rep(i, N) if (!sub[i].cmp(sub[i].get(i0, j0),
                                  sub[i].get(i1, j1))) return false;
        return true;
    }
};

#ifndef NOMAIN_HASH

int main() {
    const vector<ll> HMOD = {1000001237, 1000003931};
    //   01234567890123456789012
    string s = "abracadabra abracadabra";
    HashM h(s, HMOD);
    rep(i0, s.size() + 1) repx(j0, i0, s.size() + 1) rep(i1, s.size() + 1)
        repx(j1, i1, s.size() + 1) {
        bool eq = h.cmp(h.get(i0, j0), h.get(i1, j1));
        bool eq2 = s.substr(i0, j0 - i0) == s.substr(i1, j1 - i1);
        if (eq != eq2) {
            cout << " hash says strings \"" << s.substr(i0, j0 - i0) << "\" "
                 << (eq ? "==" : "!=") << " \"" << s.substr(i1, j1 - i1)
                 << "\" but in reality they are " << (eq2 ? "==" : "!=")
                 << endl;
        }
    }
}

#endif
