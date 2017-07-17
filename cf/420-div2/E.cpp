#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;
typedef vector<vector<int>> Matrix;

const int MOD = 1e9 + 7;

Matrix mult(const Matrix& A, const Matrix& B) {
    int n = A.size(), m = B[0].size(), k = B.size();
    Matrix C(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int t = 0; t < k; ++t) {
                C[i][j] += (A[i][t] * 1ll * B[t][j]) % MOD;
                if (C[i][j] >= MOD) C[i][j] -= MOD;
            }
        }
    }
    return C;
}

Matrix bin_pow(Matrix A, ll n) {
    Matrix res(A.size(), vector<int>(A.size()));
    for (int i = 0; i < res.size(); ++i) res[i][i] = 1;
    while (n > 0) {
        if (n % 2 == 1) {
            res = mult(res, A);
        }
        A = mult(A, A);
        n >>= 1;
    }
    return res;
}

int main() {
#if __APPLE__
    freopen("E.in", "r", stdin);
    freopen("E.out", "w", stdout);
#endif

    int n;
    ll k;
    scanf("%d%lld", &n, &k);

    vector<ll> a(n), b(n), c(n);
    for (int i = 0; i < n; ++i) {
        scanf("%lld%lld%lld", &a[i], &b[i], &c[i]);
        if (i == n - 1) b[i] = k;
    }

    vector<vector<int>> cur(1, vector<int>(c[0] + 1));
    cur[0][0] = 1;
    for (int i = 0; i < n; ++i) {
        ll sz = c[i] + 1;
        cur[0].resize(sz);
        Matrix A(sz, vector<int>(sz));
        for (int j = 0; j < sz; ++j) {
            if (j - 1 >= 0) A[j - 1][j] = 1;
            A[j][j] = 1;
            if (j + 1 < sz) A[j + 1][j] = 1;
        }
        ll len = b[i] - a[i];
        A = bin_pow(A, len);
        cur = mult(cur, A);
    }

    printf("%d\n", cur[0][0]);
}
