#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 10;

struct Dist {
    int V, O, M, U;
    int need;
};

int main() {
    int n;
    scanf("%d", &n);

    vector<Dist> ds(n + 1);
    int sum = 0;
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d%d%d", &ds[i].V, &ds[i].O, &ds[i].M, &ds[i].U);
        int need = (ds[i].O + ds[i].M + ds[i].U) / 2 + 1;
        if (ds[i].M >= need || need - ds[i].O > ds[i].U) {
            ds[i].need = -1;
        } else if (ds[i].O >= need) {
            ds[i].need = 0;
        } else {
            ds[i].need = need - ds[i].O;
        }
        sum += ds[i].V;
    }

    vector<vector<int>> dp(n + 1, vector<int>(sum + 1, INF));
    dp[0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= sum; ++j) {
            dp[i][j] = min(dp[i][j], dp[i - 1][j]);
            if (ds[i].need != -1 && j + ds[i].V <= sum) {
                dp[i][j + ds[i].V] = min(dp[i][j + ds[i].V], dp[i - 1][j] + ds[i].need);
            }
        }
    }

    int need = sum / 2 + 1;
    int ans = INF;
    for (int i = need; i <= sum; ++i) {
        ans = min(ans, dp[n][i]);
    }

    if (ans == INF) {
        puts("impossible");
    } else {
        printf("%d\n", ans);
    }
}
