#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("chemcode.in", "r", stdin);
    freopen("chemcode.out", "w", stdout);

    string s;
    while (cin >> s) {
        int n = (int)s.length();

        int m;
        scanf("%d", &m);

        vector<string> a(m);
        for (int i = 0; i < m; i++) {
            cin >> a[i];
        }

        s = "#" + s;

        int dp[n + 1];
        memset(dp, 127, sizeof dp);
        const int INF = dp[0];

        dp[0] = 0;
        for (int i = 1; i <= n; i++) {
            string prev = "";
            prev += s[i - 1];
            prev += s[i];
            for (int j = 0; j < m; j++) {
                if (prev == a[j]) {
                    dp[i] = min(dp[i], dp[i - 2] + 1);
                }
                if (a[j].find(s[i]) != string::npos) {
                    dp[i] = min(dp[i], dp[i - 1] + 1);
                }
            }
        }

        if (dp[n] < INF) {
            printf("%d\n", dp[n]);
        } else {
            puts("-1");
        }
    }
}
