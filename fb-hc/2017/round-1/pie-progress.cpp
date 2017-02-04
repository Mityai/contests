#include <bits/stdc++.h>
using namespace std;

const int INF = 2e9;

int main() {
    int t;
    scanf("%d", &t);

    for (int test = 1; test <= t; ++test) {
        int n, m;
        scanf("%d%d", &n, &m);

        int c[n + 1][m + 1];
        for (int i = 1; i <= n; ++i) {
            c[i][0] = 0;
            for (int j = 1; j <= m; ++j) {
                scanf("%d", &c[i][j]);
            }
            sort(c[i] + 1, c[i] + m + 1);
        }

        int dp[n + 1][n + 1];
        for (int i = 0; i <= n; ++i) for (int j = 0; j <= n; ++j) dp[i][j] = INF;

        dp[0][0] = 0;
        for (int day = 1; day <= n; ++day) {
            for (int took = day - 1; took <= n; ++took) {
                int sum = 0;
                for (int take = 0; took + take <= n && take <= m; ++take) {
                    sum += c[day][take];
                    dp[day][took + take] = min(dp[day][took + take], dp[day - 1][took] + sum + take * take);
                }
            }
        }
        printf("Case #%d: %d\n", test, dp[n][n]);
    }
}
