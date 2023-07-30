
#include "../common.h"

// find maximal palindromes (and therefore all palindromes) in O(n).
// returns a vector of positions, with one position for every character and in
// between characters.
//
// a   b   c   c   c
// 0 1 2 3 4 5 6 7 8
// 1 0 1 0 1 2 3 2 1
void manacher(const string& s, vector<int>& p) {
    int N = s.size(), P = 2 * N - 1;
    p.assign(P, 0);
    int l = 0, r = -1;
    rep(i, P) {
        int d = (r >= i ? min(p[l + r - i], r - i + 2) : i % 2);
        while (i - d >= 0 && i + d < P && s[(i - d) / 2] == s[(i + d) / 2])
            d += 2;
        p[i] = d;
        if (i + d - 2 > r) l = i - d + 2, r = i + d - 2;
    }
    rep(i, P) p[i] -= 1;
}

#ifndef NOMAIN_PALIN

void test(const string& s) {
    vector<int> p;
    manacher(s, p);
    cout << "palindromes of string \"" << s << "\":" << endl;
    rep(i, p.size()) {
        for (int k = i % 2; k < p[i]; k += 2) {
            cout << "  \"" << s.substr((i - k) / 2, k + 1) << "\"" << endl;
        }
    }
}

int main() {
    test("hello");
    test("abracadabra");
    test("abcba");
    test("abba");
    test("cada");
}

#endif
