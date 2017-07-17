#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);

    int n, k;
    cin >> n >> k;

    string s;
    cin >> s;

    s = "$" + s;

    bool dp[n + 1][k + k + 1];
    int p[n + 1][k + k + 1]; // 0 -- D, 1 -- L, 2 -- W
    memset(dp, 0, sizeof dp);
    memset(p, -1, sizeof p);
    dp[0][k] = true;

    for (int i = 1; i <= n; ++i) {
        for (int j = (i != n); j <= k + k - (i != n); ++j) {
            if (s[i] == 'D') {
                if (dp[i - 1][j]) {
                    dp[i][j] = true;
                    p[i][j] = 0;
                }
            } else if (s[i] == 'W') {
                if (j - 1 >= 0 && dp[i - 1][j - 1]) {
                    dp[i][j] = true;
                    p[i][j] = 2;
                }
            } else if (s[i] == 'L') {
                if (j + 1 <= k + k && dp[i - 1][j + 1]) {
                    dp[i][j] = true;
                    p[i][j] = 1;
                }
            } else {
                if (dp[i - 1][j]) {
                    dp[i][j] = true;
                    p[i][j] = 0;
                } else if (j - 1 >= 0 && dp[i - 1][j - 1]) {
                    dp[i][j] = true;
                    p[i][j] = 2;
                } else if (j + 1 <= k + k && dp[i - 1][j + 1]) {
                    dp[i][j] = true;
                    p[i][j] = 1;
                }
            }
        }
    }

    int v = -1;
    if (dp[n][0]) v = 0;
    if (dp[n][k + k]) v = k + k;

    if (v == -1) {
        puts("NO");
    } else {
        string ans;
        for (int k = n; k >= 1; --k) {
            if (p[k][v] == 0) {
                ans += 'D';
            } else if (p[k][v] == 1) {
                ans += 'L';
                ++v;
            } else {
                ans += 'W';
                --v;
            }
        }
        reverse(ans.begin(), ans.end());
        cout << ans << '\n';
    }
}
