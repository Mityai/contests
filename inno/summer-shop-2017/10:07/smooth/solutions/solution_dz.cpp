#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<vector<int>> M;

const int DIG = 9;
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
    int n;
    scanf("%d", &n);

    M f(1, vector<int>(DIG + 1));
    for (int i = 1; i <= DIG; ++i) f[0][i] = 1;
    M A(DIG + 1, vector<int>(DIG + 1));
    for (int i = 0; i <= DIG; ++i) {
        if (i - 1 >= 0) A[i - 1][i] = 1;
        A[i][i] = 1;
        if (i + 1 <= DIG) A[i + 1][i] = 1;
    }

    f = f * bin_pow(A, n - 1);
    int ans = 0;
    for (int i = 0; i <= DIG; ++i) {
        ans = (ans + f[0][i]) % MOD;
    }

    printf("%d\n", ans);
}
