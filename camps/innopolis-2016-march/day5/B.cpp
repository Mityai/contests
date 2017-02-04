#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MOD = 1e9 + 7;
const int N = 4e3;

int n;
int a[N + 2][N + 2];
int sum[N + 2][N + 2];
int cnt[N + 2][N + 2];

bool isMatrix(int i1, int j1, int i2, int j2) {
    return sum[i2][j2] - sum[i1 - 1][j2] - sum[i2][j1 - 1] + sum[i1 - 1][j1 - 1] ==
        (i2 - i1 + 1) * (j2 - j1 + 1);
}

int main() {
    freopen("matrix.in", "r", stdin);
    freopen("matrix.out", "w", stdout);

    cin >> n;

    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        for (int j = 1; j <= n; j++) {
            a[i][j] = s[j - 1] - '0';
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + a[i][j];
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cnt[i][j] = 2 * cnt[i - 1][j] + 2 * cnt[i][j - 1] - cnt[i - 1][j - 1] + 1;
        }
    }

    cout << cnt[1][1] << ' ' << cnt[1][2] << endl;

    ll all = 0;
    for (int i1 = 1; i1 <= n; i1++) {
        for (int j1 = 1; j1 <= n; j1++) {
            for (int i2 = i1; i2 <= n; i2++) {
                for (int j2 = j1; j2 <= n; j2++) {
                    if (isMatrix(i1, j1, i2, j2)) {
                        all++;
                    }
                }
            }
        }
    }
    cout << all << endl;

    ll ans = 0;
    for (int i1 = 1; i1 <= n; i1++) {
        for (int j1 = 1; j1 <= n; j1++) {
            for (int i2 = i1; i2 <= n; i2++) {
                for (int j2 = j1; j2 <= n; j2++) {
                    if (isMatrix(i1, j1, i2, j2)) {
                        ans += (all - cnt[i2 - i1 + 1][j2 - j1 + 1]) % MOD;
                        ans %= MOD;
                    }
                }
            }
        }
    }

    printf("%lld\n", ans);
}
