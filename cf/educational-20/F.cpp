#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

typedef long long ll;

int main() {
    int n;
    scanf("%d", &n);

    int a[n];
    for (int i = 0; i < n; ++i) {
        scanf("%d", a + i);
    }

    map<int, int> cnt;
    vector<int> lprime(n);
    vector<vector<int>> pr(n);
    for (int i = 0; i < n; ++i) {
        ll x = a[i];
        for (ll p = 2; p * p <= x; ++p) {
            if (x % p == 0) {
                pr[i].push_back(p);
            }
            while (x % p == 0) {
                x /= p;
            }
        }
        if (x != 1) {
            pr[i].push_back(x);
        }

        for (int mask = 1; mask < (1 << pr[i].size()); ++mask) {
            int x = 1;
            for (int j = 0; j < pr[i].size(); ++j) {
                if ((mask >> j) & 1) {
                    x *= pr[i][j];
                }
            }
            int sgn = 1;
            if (__builtin_popcount(mask) % 2 == 0) {
                sgn = -1;
            }
            lprime[i] += sgn * cnt[x];
            ++cnt[x];
        }
        lprime[i] = i - lprime[i];
    }

    cnt.clear();
    vector<int> rprime(n);
    for (int i = n - 1; i >= 0; --i) {
        for (int mask = 1; mask < (1 << pr[i].size()); ++mask) {
            int x = 1;
            for (int j = 0; j < pr[i].size(); ++j) {
                if ((mask >> j) & 1) {
                    x *= pr[i][j];
                }
            }
            int sgn = 1;
            if (__builtin_popcount(mask) % 2 == 0) {
                sgn = -1;
            }
            rprime[i] += sgn * cnt[x];
            ++cnt[x];
        }
        rprime[i] = n - i - 1 - rprime[i];
    }

    vector<int> two(n + 1);
    two[0] = 1;
    for (int i = 1; i <= n; ++i) {
        two[i] = (two[i - 1] * 2ll) % MOD;
    }

    vector<vector<int>> cnk(n + 1, vector<int>(n + 1));
    for (int i = 0; i <= n; ++i) {
        cnk[i][0] = cnk[i][i] = 1;
        for (int j = 1; j < i; ++j) {
            cnk[i][j] = (cnk[i - 1][j - 1] + cnk[i - 1][j]) % MOD;
        }
    }

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        int rest = i - lprime[i];
        int rrest = n - i - 1 - rprime[i];
        cout << a[i] << ": " << lprime[i] << ' ' << rprime[i] << endl;
        int cur = ((((two[lprime[i]] - (a[i] != 1)) * 1ll * two[rest]) % MOD) * 1ll * two[rrest]) % MOD;
        cout << cur << endl;
        ans = (ans + cur) % MOD;
    }

    printf("%d\n", ans);
}
