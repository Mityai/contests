#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

const int MOD = 1e9 + 7;
const int N = 76;

int num[N][N];

int tonum(string s) {
    int ret = 0;
    for (char c : s) {
        ret = ret * 2 + c - '0';
    }
    return ret;
}

void calc(string& s, int n) {
    for (int i = 1; i <= n; i++) {
        for (int len = 1; i + len - 1 <= n; len++) {
            num[i][i + len - 1] = tonum(s.substr(i, len));
        }
    }
}

int dp[N][1 << 20];

int main() {
#if __APPLE__
    freopen("D.in", "r", stdin);
    freopen("D.out", "w", stdout);
#endif

    int n;
    scanf("%d", &n);

    string s;
    cin >> s;

    s = "$" + s;
    calc(s, n);

    for (int i = 0; i <= n; i++) {
        dp[i][0] = 1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j <= n; j++) {
            int x = num[i + 1][j];
            if (x > 20) {
                break;
            }
            if (x == 0) continue;
            --x;
            for (int mask = 0; mask < (1 << 20); ++mask) {
                int& newdp = dp[j][mask | (1 << x)];
                newdp = (newdp + dp[i][mask]) % MOD;
            }
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        for (int k = 1; k <= 20; k++) {
            ans = (ans + dp[i][(1 << k) - 1]) % MOD;
        }
    }
    printf("%d\n", ans);
}

