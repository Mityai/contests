#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

const ll INF = 1e17;

int main() {
#if __APPLE__
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
#endif

    int n, k, p;
    while (scanf("%d%d%d", &n, &k, &p) == 3) {
        vector<int> a(n + 1);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
        }
        sort(a.begin() + 1, a.end());

        vector<int> b(k + 1);
        for (int i = 1; i <= k; ++i) {
            scanf("%d", &b[i]);
        }
        sort(b.begin() + 1, b.end());

        vector<vector<ll>> dp(n + 1, vector<ll>(k + 1, INF));
        for (int i = 0; i <= k; ++i)
            dp[0][i] = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = i; j <= k; ++j) {
                dp[i][j] = min(dp[i][j - 1], max(dp[i - 1][j - 1], ll(abs(b[j] - a[i]) + abs(b[j] - p))));
            }
        }
        ll ans = INF;
        for (int i = n; i <= k; ++i) {
            ans = min(ans, dp[n][i]);
        }
        printf("%lld\n", ans);
    }
}
