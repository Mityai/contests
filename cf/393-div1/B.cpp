#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

const ll INF = LLONG_MAX;

int main() {
#if __APPLE__
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif

    int n;
    while (scanf("%d", &n) == 1) {
        vector<int> t(n + 1);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &t[i]);
        }

        vector<ll> dp(n + 1, INF);
        dp[0] = 0;
        set<pair<ll, ll>> mnj, mnk;
        mnj.insert({dp[0], 0});
        mnk.insert({dp[0], 0});
        for (int i = 1, j = 0, k = 0; i <= n; ++i) {
            dp[i] = min(dp[i], dp[i - 1] + 20);
            while (t[i] - t[j + 1] + 1 > 1440) {
                mnj.erase({dp[j], j});
                ++j;
            }
            while (t[i] - t[k + 1] + 1 > 90) {
                mnk.erase({dp[k], k});
                ++k;
            }
            if (!mnj.empty()) {
                ll mn = mnj.begin()->fi;
                dp[i] = min(dp[i], mn + 120);
            }
            if (!mnk.empty()) {
                ll mn = mnk.begin()->fi;
                dp[i] = min(dp[i], mn + 50);
            }
            mnj.insert({dp[i], i});
            mnk.insert({dp[i], i});
        }

        for (int i = 1; i <= n; ++i) {
            printf("%lld\n", dp[i] - dp[i - 1]);
        }
    }
}
