#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

const ll MOD = 175781251;
const int N = 1e5;

ll fact[N];

ll binpow(ll a, ll n) {
    if (n == 0) return 0LL;
    if (n == 1) return a % MOD;
    ll b = binpow(a, n >> 1LL);
    b = (b * b) % MOD;
    if (n & 1LL) b = (b * a) % MOD;
    return b;
}

ll C(ll n, ll k) {
    return ((fact[n] * binpow(fact[k], MOD - 2)) % MOD * binpow(fact[n - k], MOD - 2)) % MOD;
}

int main() {
#if __APPLE__
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
#endif

    fact[0] = 1;
    for (ll i = 1; i < N; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }

    int n;
    for (n = 1; n <= 100; n++) {
        if (n == 0) break;
        printf("Test n = %d\n", n);
        ll ans = 0;
        for (int v = 1; v < n; v++) {
            for (int u = 1; u + v <= n; u++) {
                //cout << u << ' ' << v << endl;
                ans = (ans + ((C(n, v) * C(n - v, u)) % MOD * binpow(2, u * v)) % MOD) % MOD;
            }
        }
        ans = (ans * binpow(2, MOD - 2)) % MOD;
        printf("%lld\n", (ans + 1) % MOD);
    }
}
