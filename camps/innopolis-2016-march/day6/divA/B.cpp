#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

void add(int &x, int y) {
    x += y;
    if (x >= MOD) x -= MOD;
}

const int N = 502;
int dp[2][N][N];

int main() {
#if __APPLE__
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif

    int n;
    scanf("%d", &n);

    vector<string> a(n + 2);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] = "." + a[i] + ".";
    }
    a[0] = string(n + 2, '.');
    a[n + 1] = string(n + 2, '.');

    dp[0][1][n] = (a[1][1] == a[n][n]);

    for (int sum = 2; sum <= n; sum++) {
        int p = (sum & 1);
        int q = 1 - p;
        for (int i1 = 1; i1 <= n - 1; i1++) {
            int j1 = sum - i1;
            if (1 <= j1 && j1 <= n) {
                for (int i2 = n; i2 >= 2; i2--) {
                    int j2 = 2 * n - sum - i2 + 2;
                    if (1 <= j2 && j2 <= n) {
                        if (a[i1][j1] == a[i2][j2]) {
                            int ADD = dp[p][i1][i2];
                            if (a[i1][j1 + 1] == a[i2][j2 - 1]) {
                                add(dp[q][i1][i2], ADD);
                            }
                            if (a[i1][j1 + 1] == a[i2 - 1][j2]) {
                                add(dp[q][i1][i2 - 1], ADD);
                            }
                            if (a[i1 + 1][j1] == a[i2][j2 - 1]) {
                                add(dp[q][i1 + 1][i2], ADD);
                            }
                            if (a[i1 + 1][j1] == a[i2 - 1][j2]) {
                                add(dp[q][i1 + 1][i2 - 1], ADD);
                            }
                        }
                    }
                }
            }
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                dp[p][i][j] = 0;
            }
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        add(ans, dp[(n + 1) % 2][i][i]);
    }

    printf("%d\n", ans);
}
