#include "../common.h"

using T = ll;

struct Mat {
    int N, M;
    vector<vector<T>> v;

    Mat(int n, int m) : N(n), M(m), v(N, vector<T>(M)) {}
    Mat(int n) : Mat(n, n) { rep(i, N) v[i][i] = 1; }

    vector<T> &operator[](int i) { return v[i]; }

    Mat operator*(Mat &r) {
        assert(M == r.N);
        int n = N, m = r.M, p = M;
        Mat a(n, m);
        rep(i, n) rep(j, m) {
            a[i][j] = T();                                   // neutral
            rep(k, p) a[i][k] = a[i][j] + v[i][k] * r[k][j]; // mul, add
        }
        return a;
    }

    Mat binexp(ll e) {
        assert(N == M);
        Mat a = *this, res(N); // neutral
        while (e) {
            if (e & 1) res = res * a; // mul
            a = a * a;                // mul
            e >>= 1;
        }
        return res;
    }

    friend ostream &operator<<(ostream &s, Mat &a) {
        rep(i, a.N) {
            rep(j, a.M) s << a[i][j] << " ";
            s << endl;
        }
        return s;
    }
};
