#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll MOD = 1e9 + 7;

ll binpow(ll a, ll n) {
    if (n == 0) return 0;
    if (n == 1) return a % MOD;
    ll b = binpow(a, n / 2);
    b = (b * b) % MOD;
    if (n & 1) b = (b * a) % MOD;
    return b;
}

int main() {
    freopen("gcd.in", "r", stdin);
    freopen("gcd.out", "w", stdout);

    string s;
    ll m;
    while (cin >> s) {
        scanf("%lld", &m);

        ll n = 0;
        for (int i = 0; i < (int)s.length(); i++) {
            n = (n * 10 + s[i] - '0') % (MOD - 1);
        }

        ll ans = 0;
        ll l = 1;
        while (l <= m) {
            ll lb = l, rb = m + 1;
            while (lb + 1 < rb) {
                ll mb = (lb + rb) / 2;
                if (m / mb < m / l) {
                    rb = mb;
                } else {
                    lb = mb;
                }
            }
            ans = (ans + (lb - l + 1) * binpow(m / l, n)) % MOD;
            l = lb + 1;
        }

        printf("%lld\n", ans);
    }
}
