#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int MOD = 1e9 + 7;
const int N = 2000;
const int M = 1e8;

int fact[M + 1];
int rev[M + 1];

int binpow(int a, int n) {
    if (n == 0) return 1;
    if (n == 1) return a % MOD;
    int b = binpow(a, n / 2);
    b = (b * 1ll * b) % MOD;
    if (n & 1) {
        b = (b * 1ll * a) % MOD;
    }
    return b;
}

int cnk(int n, int k) {
    if (n <= M) {
        return ((fact[n] * 1ll * rev[k]) % MOD * 1ll * rev[n - k]) % MOD;
    }
    int ret = 1;
    for (int i = k + 1; i <= n; ++i) {
        ret = (ret * 1ll * i) % MOD;
    }
    ret = (ret * 1ll * rev[n - k]) % MOD;
    return ret;
}

int main() {
    double tm = clock();
    fact[0] = 1;
    for (int i = 1; i <= M; ++i) {
        fact[i] = (fact[i - 1] * 1ll * i) % MOD;
    }
    for (int i = 0; i <= M; ++i) {
        rev[i] = binpow(fact[i], MOD - 2);
    }
    cerr << "time " << (clock() - tm) / CLOCKS_PER_SEC << endl;
    cerr << "testing" << endl;

    int t;
    scanf("%d", &t);

    for (int test = 1; test <= t; ++test) {
        int n, m;
        scanf("%d%d", &n, &m);

        vector<int> a(n);
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%d", &a[i]);
            sum += a[i];
        }

        int ans = 0;
        if (n == 1) {
            ans = m;
        } else {
            for (int i = 0; i < n; ++i) {
                for (int j = i + 1; j < n; ++j) {
                    int cur = sum - a[i] - a[j];
                    int left = (m - 1) - a[i] - a[j];
                    int free = left - 2 * cur;
                    if (free >= 0) {
                        ans = (ans + ((2ll * fact[n - 2]) % MOD) * 1ll * cnk(n + free, free)) % MOD;
                    }
                }
            }
        }

        printf("Case #%d: %d\n", test, ans);
    }
    cerr << "time " << (clock() - tm) / CLOCKS_PER_SEC << endl;
}
