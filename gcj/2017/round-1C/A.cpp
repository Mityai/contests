#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

const double pi = acos(-1);

int main() {
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);

    int t;
    scanf("%d", &t);

    for (int test = 1; test <= t; ++test) {
        int n, k;
        scanf("%d%d", &n, &k);

        vector<pair<int, int>> a(n + 1);
        for (int i = 1; i <= n; ++i) {
            scanf("%d%d", &a[i].fi, &a[i].se);
        }

        sort(a.rbegin(), a.rend() - 1);

        vector<vector<double>> dp(n + 1, vector<double>(k + 1));
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j <= k; ++j) {
                dp[i][j] = dp[i - 1][j];
                if (j > 0) {
                    if (j == 1) {
                        dp[i][j] = max(dp[i][j], pi * a[i].fi * 2.0 * a[i].se + pi * a[i].fi * a[i].fi);
                    } else {
                        dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + pi * a[i].fi * 2.0 * a[i].se);
                    }
                }
            }
        }

        double ans = 0;
        for (int i = 1; i <= n; ++i) {
            ans = max(ans, dp[i][k]);
        }

        printf("Case #%d: %.10lf\n", test, ans);
    }
}
