#include <bits/stdc++.h>
using namespace std;

typedef unsigned int ui;
typedef long long ll;

const ui LCM = 4 * 7 * 9;

typedef vector<vector<ui>> M;

M operator * (const M& A, const M& B) {
    M C(A.size(), vector<ui>(B[0].size()));
    for (int i = 0; i < C.size(); ++i) {
        for (int j = 0; j < C[i].size(); ++j) {
            for (int k = 0; k < B.size(); ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

M bin_pow(M A, ll n) {
    M ans = M(A.size(), vector<ui>(A.size()));
    for (size_t i = 0; i < A.size(); ++i) ans[i][i] = 1;
    while (n > 0) {
        if (n & 1) ans = ans * A;
        A = A * A;
        n >>= 1;
    }
    return ans;
}

int main() {
    ll n;
    scanf("%lld", &n);

    M A(LCM, vector<ui>(LCM));
    for (int rem = 0; rem < LCM; ++rem) {
        for (int d = 1; d <= 9; ++d) {
            if ((rem * 10 + d) % d == 0) {
                ++A[rem][(rem * 10 + d) % LCM];
            }
        }
    }

    M f(LCM, vector<ui>(1));
    A = bin_pow(A, n);
    f = A * f;
    printf("%u\n", f[0][0]);
}
