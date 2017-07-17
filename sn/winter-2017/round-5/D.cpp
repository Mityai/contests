#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    int q, n, D;
    scanf("%d%d%d", &q, &n, &D);

    string f1, f2;
    cin >> f1 >> f2;

    f1 = "#" + f1;
    f2 = "$" + f2;

    ll dp[n + 1][D + 1];
    memset(dp, 0, sizeof dp);
    dp[0][0] = 1;

    for (int i = 1; i <= n; ++i) {
        for (int prevd = 0; prevd <= D; ++prevd) {
            for (int curq = 0; curq < q; ++curq) {
                int curdist = (f1[i] - '0' != curq) + (f2[i] - '0' != curq);
                if (prevd + curdist <= D) {
                    dp[i][prevd + curdist] += dp[i - 1][prevd];
                }
            }
        }
    }

    printf("%lld\n", dp[n][D]);
}
