#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

const ll INF = 1e18;

int main() {
#if __APPLE__
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif

    ios_base::sync_with_stdio(false);

    int n;
    ll a, b, c;
    cin >> n >> a >> b >> c;

    vector<vector<char>> key(n, vector<char>(26, false));
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        for (char c : s) {
            if ('a' <= c && c <= 'z') {
                key[i][c - 'a'] = true;
            }
        }
    }

    string s;
    cin >> s;

    int m = s.length();
    s = "$" + s;

    vector<vector<ll>> dp(m + 1, vector<ll>(n, INF));
    dp[0][0] = 0;
    for (int j = 1; j < n; ++j) {
        if (j == 1) {
            dp[0][j] = a;
        } else {
            dp[0][j] = dp[0][j - 1] + b;
        }
    }

    for (int i = 1; i <= m; ++i) {
        int x = s[i] - 'a';
        for (int j = 0; j < n; ++j) {
            if (key[j][x]) {
                dp[i][j] = min(dp[i][j], dp[i - 1][j] + c);
            }
        }
        ll best = INF;
        for (int j = 0; j < n + n; ++j) {
            int k = j; if (k >= n) k -= n;
            dp[i][k] = min(dp[i][k], best);
            if (key[k][x] && best + b > dp[i][k] + a) {
                best = dp[i][k] + a;
            } else {
                best += b;
            }
        }
    }

    ll ans = INF;
    for (int i = 0; i < n; ++i) {
        ans = min(ans, dp[m][i]);
    }

    if (ans == INF) {
        ans = -1;
    }

    cout << ans << '\n';
}
