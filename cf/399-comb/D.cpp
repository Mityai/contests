#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

const double eps = 5e-8;

int main() {
#if __APPLE__
    freopen("D.in", "r", stdin);
    freopen("D.out", "w", stdout);
#endif

    int k, q;
    while (scanf("%d%d", &k, &q) == 2) {
        vector<pair<int, int>> p(q);
        for (int i = 0; i < q; ++i) {
            scanf("%d", &p[i].fi);
            p[i].se = i;
        }
        sort(p.begin(), p.end());

        vector<int> ans(q);

        vector<vector<double>> dp(2, vector<double>(k + 1));
        dp[0][0] = 1.0;
        for (int i = 0, day = 1; i < q; ++i) {
            while (dp[(day & 1) ^ 1][k] * 2000 < p[i].fi - eps) {
                for (int have = 0; have <= k; ++have) {
                    if (have + 1 <= k) {
                        dp[day & 1][have + 1] += double(k - have) / k * dp[(day & 1) ^ 1][have];
                    }
                    dp[day & 1][have] += double(have) / k * dp[(day & 1) ^ 1][have];
                }
                ++day;
                dp[day & 1].assign(k + 1, 0);
            }
            ans[p[i].se] = day - 1;
        }

        for (int i = 0; i < q; ++i) {
            printf("%d\n", ans[i]);
        }
    }
}
