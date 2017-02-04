#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll INF = LLONG_MAX - 1234567890;

int main() {
    freopen("sms.in", "r", stdin);
    freopen("sms.out", "w", stdout);

    int n, m;
    scanf("%d%d", &n, &m);

    int a[n + 1];
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
    }

    ll dp[m + 1][n + 1];
    int p[m + 1][n + 1];
    memset(p, -1, sizeof p);
    for (int i = 0; i <= m; i++) for (int j = 0; j <= n; j++)
        dp[i][j] = INF;

    dp[0][0] = 0;

    for (int but = 1; but <= m; but++) {
        for (int st = 1; st <= n; st++) {
            for (int pr = 0; pr < st; pr++) {
                ll add = 0;
                for (int k = pr + 1; k <= st; k++) {
                    add += (k - pr) * a[k];
                }
                if (dp[but][st] > dp[but - 1][pr] + add) {
                    dp[but][st] = dp[but - 1][pr] + add;
                    p[but][st] = pr;
                }
            }
        }
    }

    int but = 0;
    for (int i = 1; i <= m; i++) {
        if (dp[i][n] < dp[but][n]) but = i;
    }

    int ans[m];
    memset(ans, 0, sizeof ans);

    for (int i = but, x = n; i > 0; x = p[i][x], i--) {
        ans[i - 1] += x - p[i][x];
    }

    for (int i = 0; i < m; i++) {
        printf("%d ", ans[i]);
    }
    puts("");
}
