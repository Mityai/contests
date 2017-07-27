#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<vector<int>> M;

const int MOD = 1e9 + 7;

M operator * (const M& A, const M& B) {
    M C(A.size(), vector<int>(B[0].size()));
    for (int i = 0; i < C.size(); ++i) {
        for (int j = 0; j < C[i].size(); ++j) {
            for (int k = 0; k < B.size(); ++k) {
                C[i][j] += (A[i][k] * 1ll * B[k][j]) % MOD;
                if (C[i][j] >= MOD) C[i][j] -= MOD;
            }
        }
    }
    return C;
}

M bin_pow(M A, ll n) {
    M ans = M(A.size(), vector<int>(A.size()));
    for (size_t i = 0; i < A.size(); ++i) ans[i][i] = 1;
    while (n > 0) {
        if (n & 1) ans = ans * A;
        A = A * A;
        n >>= 1;
    }
    return ans;
}

int main() {
#if not __APPLE__
    freopen("fibonacci.in", "r", stdin);
    freopen("fibonacci.out", "w", stdout);
#endif

    int k;
    ll n;
    scanf("%d%lld", &k, &n);

    M f(1, vector<int>(k + 1));
    for (int i = 0; i < k; ++i) {
        scanf("%d", &f[0][i]);
    }
    f[0][k] = f[0][0];

    M A(k + 1, vector<int>(k + 1));
    for (int i = 0; i <= k - 2; ++i) {
        A[i + 1][i] = 1;
    }
    for (int i = k - 1; i >= 0; --i) {
        scanf("%d", &A[i][k - 1]);
    }
    A[1][k] = A[k][k] = 1;

    f = f * bin_pow(A, n);
    printf("%d %d\n", f[0][0], f[0][k]);
}
