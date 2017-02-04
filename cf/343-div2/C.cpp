#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

const int B = 2222;
const int N = 2222;

int dp[N][B];

int main() {
    dp[0][0] = 1;
    for (int i = 1; i < N; i++) {
        for (int j = 0; j + 1 < B; j++) {
            if (j > 0) dp[i][j] = (dp[i][j] + dp[i - 1][j - 1]) % MOD;
            dp[i][j] = (dp[i][j] + dp[i - 1][j + 1]) % MOD;
        }
    }

    int n, m;
    scanf("%d%d", &n, &m);

    string s;
    cin >> s;

    int mn = 0;
    int bal = 0;
    for (char c : s) {
        if (c == '(') bal++;
        else bal--;
        mn = min(mn, bal);
    }

    int ans = 0;
    for (int i = 0; i <= n - m; i++) {
        for (int b = -mn; b <= i; b++) {
            int minb = b + mn;
            int maxb = b + bal;
            if (maxb < B) {
                ans = (ans + (dp[i][b] * 1LL * dp[n - m - i][maxb]) % MOD) % MOD;
            }
        }
    }
    cout << ans << endl;
}
