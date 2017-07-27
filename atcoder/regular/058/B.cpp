#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

const int N = 1e5;

int fact[N + N - 2 + 1];

int bin_pow(int x, int a) {
    int res = 1;
    while (a > 0) {
        if (a & 1) {
            res = (res * 1ll * x) % MOD;
        }
        x = (x * 1ll * x) % MOD;
        a >>= 1;
    }
    return res;
}

int rev(int x) {
    return bin_pow(x, MOD - 2);
}

int mult(int a, int b) {
    return (a * 1ll * b) % MOD;
}

int sum(int a, int b) {
    a += b;
    if (a >= MOD) a -= MOD;
    return a;
}

int cnk(int n, int k) {
    return mult(mult(fact[n], rev(fact[n - k])), rev(fact[k]));
}

int main() {
    fact[0] = 1;
    for (int i = 1; i <= N + N - 2; ++i) {
        fact[i] = mult(i, fact[i - 1]);
    }

    int H, W, A, B;
    scanf("%d%d%d%d", &H, &W, &A, &B);

    int ans = 0;
    for (int x1 = B + 1; x1 <= W; ++x1) {
        int y1 = H - A;
        int x2 = W - x1 + 1;
        int y2 = A;
        ans = sum(ans, mult(cnk(x1 + y1 - 2, x1 - 1), cnk(x2 + y2 - 2, x2 - 1)));
    }
    printf("%d\n", ans);
}
