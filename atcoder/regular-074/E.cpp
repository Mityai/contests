#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

const int MOD = int(1e9) + 7;

int main() {
#if __APPLE__
    freopen("E.in", "r", stdin);
    freopen("E.out", "w", stdout);
#endif

    int n, m;
    while (scanf("%d%d", &n, &m) == 2) {
        vector<vector<pair<int, int>>> a(n + 1);
        for (int i = 0; i < m; ++i) {
            int l, r, x;
            scanf("%d%d%d", &l, &r, &x);
            a[r].push_back({l, x});
        }

        ll dp[n + 2][n + 2][n + 2];
        memset(dp, 0, sizeof dp);
        dp[0][0][0] = 1;
        ll ans = 0;
        for (int r = 0; r <= n; ++r) {
            for (int g = 0; g <= n; ++g) {
                for (int b = 0; b <= n; ++b) {
                    int k = max({r, g, b});
                    for (auto& x : a[k]) {
                        int l = x.fi;
                        int c = x.se;
                        int cnt = (r >= l) + (g >= l) + (b >= l);
                        if (cnt != c) {
                            dp[r][g][b] = 0;
                            break;
                        }
                    }
                    dp[k + 1][g][b] += dp[r][g][b];
                    if (dp[k + 1][g][b] >= MOD) dp[k + 1][g][b] -= MOD;
                    dp[r][k + 1][b] += dp[r][g][b];
                    if (dp[r][k + 1][b] >= MOD) dp[r][k + 1][b] -= MOD;
                    dp[r][g][k + 1] += dp[r][g][b];
                    if (dp[r][g][k + 1] >= MOD) dp[r][g][k + 1] -= MOD;
                    if (k == n) {
                        ans += dp[r][g][b];
                        if (ans >= MOD) ans -= MOD;
                    }
                }
            }
        }

        printf("%lld\n", ans);
        return 0;
    }
}
