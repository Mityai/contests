#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

#if __APPLE__
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define eprintf(...)
#endif

void solve(int n, int k) {
    eprintf("n = %d, k = %d\n", n, k);

    map<int, int> f;
    int m = k;
    vector<int> primes;
    for (ll p = 2; p * p <= m; ++p) {
        if (m % p == 0) primes.push_back(p);
        while (m % p == 0) {
            ++f[p];
            m /= p;
        }
    }
    if (m != 1) {
        ++f[m];
        primes.push_back(m);
    }
    vector<int> has(primes.size());
    for (int i = 0; i < primes.size(); ++i) {
        has[i] = f[primes[i]];
    }

    vector<int> a(n + 1);
    vector<vector<int>> ps(n + 1, vector<int>(primes.size()));
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        int x = a[i];
        for (int j = 0; j < primes.size(); ++j) {
            ps[i][j] += ps[i - 1][j];
            int p = primes[j];
            while (x % p == 0) {
                ++ps[i][j];
                x /= p;
            }
        }
    }

    ll ans = 0;
    for (int l = 0; l <= n - 1; ++l) {
        int lb = l, rb = n + 1;
        while (lb + 1 < rb) {
            int mb = (lb + rb) / 2;
            vector<int> cur = ps[mb];
            bool ok = true;
            for (int j = 0; j < primes.size(); ++j) {
                cur[j] -= ps[l][j];
                eprintf("j = %d, prime = %d, cur[%d] = %d\n", j, primes[j], j, cur[j]);
                if (cur[j] < has[j]) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                rb = mb;
            } else {
                lb = mb;
            }
        }
        eprintf("l = %d, r = %d, add = %d\n", l, rb, n - rb + 1);
        ans += n - rb + 1;
    }

    printf("%lld\n", ans);
}

int main() {
#if __APPLE__
    freopen("E.in", "r", stdin);
    freopen("E.out", "w", stdout);
#endif

    int n, k;
    while (scanf("%d%d", &n, &k) == 2) {
        solve(n, k);
    }
}
