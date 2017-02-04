#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll INF = LLONG_MAX;

int main() {
    freopen("mars.in", "r", stdin);
    freopen("mars.out", "w", stdout);

    ll n, k;
    scanf("%lld%lld", &n, &k);

    ll ans = INF;

    ll m = k;
    for (ll p = 2; p * p <= m; p++) {
        ll cnt = 0;
        if (m % p == 0) {
            ll f = n;
            while (f > 0) {
                cnt += f / p;
                f /= p;
            }
        }
        ll inm = 0;
        while (m % p == 0) {
            m /= p;
            inm++;
        }
        if (inm > 0) {
            ans = min(ans, cnt / inm);
        }
    }

    if (m != 1) {
        ll p = m;
        ll cnt = 0;
        if (m % p == 0) {
            ll f = n;
            while (f > 0) {
                cnt += f / p;
                f /= p;
            }
        }
        ll inm = 1;
        if (inm > 0) {
            ans = min(ans, cnt / inm);
        }
    }

    printf("%lld\n", ans);
}
