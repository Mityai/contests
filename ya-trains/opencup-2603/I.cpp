#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ll;

const int N = 1e6 + 1;
const ll MX = 1e18;
const ll INF = 3e18;
const string ALPHA = "abc";

ll dp[N][3];

void pre() {
    for (int i = 0; i < 3; ++i) {
        dp[1][i] = 1;
    }
    for (int i = 2; i < N; ++i) {
        for (int a = 0; a < 3; ++a) {
            for (int b = 0; b < 3; ++b) {
                if (a != b) {
                    dp[i][a] += dp[i - 1][b];
                    if (dp[i][a] > MX) {
                        dp[i][a] = INF;
                    }
                }
            }
        }
    }
    for (int i = 2; i < N; ++i) {
        for (int j = 0; j < 3; ++j) {
            dp[i][j] += dp[i - 1][j];
            if (dp[i][j] > MX) {
                dp[i][j] = INF;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);

    pre();

    ll n, k;
    cin >> n >> k;

    string ans;
    while (k > 0 && n > 0) {
        bool ok = false;
        for (char c : ALPHA) {
            if (!ans.empty() && ans.back() == c) continue;
            if (k <= dp[n][c - 'a']) {
                ans += c;
                --n;
                --k;
                ok = true;
                break;
            } else {
                k -= dp[n][c - 'a'];
            }
        }
        if (!ok) {
            cout << "NO" << endl;
            return 0;
        }
    }

    cout << ans << endl;
}
