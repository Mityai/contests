#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

int main() {
#if __APPLE__
    freopen("D.in", "r", stdin);
    freopen("D.out", "w", stdout);
#endif

    int n, k;
    scanf("%d%d", &n, &k);

    int m;
    scanf("%d", &m);
    vector<vector<int>> d(n, vector<int>(n, -1));
    for (int i = 0; i < m; ++i) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        --u, --v;
        swap(u, v);
        if (d[u][v] == -1 || d[u][v] > c) {
            d[u][v] = c;
        }
    }

    int dp[n][n][k][2];
    memset(dp, 127, sizeof dp);
    const int INF = dp[0][0][0][0];

    for (int i = 0; i < n; ++i) {
        dp[i][i][0][0] = dp[i][i][0][1] = 0;
    }

    for (int t = 1; t < k; ++t) {
        for (int len = 1; len < n; ++len) {
            for (int l = 0; l + len < n; ++l) {
                int r = l + len;
                for (int z = l + 1; z <= r; ++z) {
                    if (d[r][l] != -1) {
                        dp[l][r][t][0] = min(dp[l][r][t][0], dp[z][r][t - 1][1] + d[r][l]);
                    }
                    if (d[z][l] != -1) {
                        dp[l][r][t][0] = min(dp[l][r][t][0], dp[z][r][t - 1][0] + d[z][l]);
                    }
                }
                for (int z = l; z <= r - 1; ++z) {
                    if (d[l][r] != -1) {
                        dp[l][r][t][1] = min(dp[l][r][t][1], dp[l][z][t - 1][0] + d[l][r]);
                    }
                    if (d[z][r] != -1) {
                        dp[l][r][t][1] = min(dp[l][r][t][1], dp[l][z][t - 1][1] + d[z][r]);
                    }
                }
            }
        }
    }

    int ans = INF;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int f = 0; f <= 1; ++f) {
                ans = min(ans, dp[i][j][k - 1][f]);
            }
        }
    }

    if (ans == INF) ans = -1;
    printf("%d\n", ans);
}
