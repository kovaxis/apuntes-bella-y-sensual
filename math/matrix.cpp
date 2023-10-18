typedef vector<vector<double>> Mat;
Mat matmul(Mat l, Mat r) {
    int n = l.N, m = r.M, p = l.M; assert(l.M == r.N);
    Mat a(n, vector<double>(m));  // neutral
    rep(i, n) rep(j, m)
        rep(k, p) a[i][j] = a[i][j] + l[i][k] * r[k][j];
    return a;
}

double reduce(vector<vector<double>> &A) {
    int n = A.size(), m = A[0].size();
    int i = 0, j = 0; double r = 1.;
    while (i < n && j < m) {
        int l = i;
        repx(k, i+1, n) if(abs(A[k][j]) > abs(A[l][j])) l=k;
        if (abs(A[l][j]) < EPS) { j++; r = 0.; continue; }
        if (l != i) { r = -r; swap(A[i], A[l]); }
        r *= A[i][j];
        for (int k = m - 1; k >= j; k--) A[i][k] /= A[i][j];
        repx(k, 0, n) {
            if (k == i) continue;
            for(int l=m-1;l>=j;l--)A[k][l]-=A[k][j]*A[i][l];
        }
        i++, j++;
    }
    return r; // returns determinant
}