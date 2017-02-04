#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll INF = LLONG_MAX;

ll pw(ll x, ll d) {
    ll ret = 1;
    for (int i = 0; i < d; i++) {
        ret *= x;
    }
    return ret;
}

int main() {
    freopen("divisors-power.in", "r", stdin);
    freopen("divisors-power.out", "w", stdout);

    ll n;
    cin >> n;

    ll ans = INF;
    for (ll d = 2; d <= 60; d++) {
        ll x = pow(n, 1.0 / d);
        while (pw(x, d) < n) x++;
        while (pw(x, d) > n) x--;
        if (pw(x, d) == n) {
            ll cnt = 0;
            for (ll i = 1; i * i <= x; i++) {
                if (x % i == 0) {
                    cnt += 2;
                    if (i * i == x) cnt--;
                }
            }
            if (cnt == d) ans = min(ans, x);
        }
    }

    if (ans == INF) puts("-1");
    else printf("%lld\n", ans);
}
