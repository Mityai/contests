#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ll n, k;
    cin >> n >> k;

    set<ll> dels;
    for (ll i = 1; i * i <= n; ++i) {
        if (n % i == 0) {
            dels.insert(i);
            dels.insert(n / i);
        }
    }

    ll ans = -1;
    for (ll g : dels) {
        ll need = n / g;
        if (k * (k + 1) / 2 <= need) {
            ans = g;
        }
    }

    if (ans == -1) {
        puts("-1");
    } else {
        ll g = ans;
        ll sum = 0;
        for (int i = 0; i < k - 1; ++i) {
            printf("%lld ", (i + 1) * g);
            sum += (i + 1) * g;
        }
        printf("%lld\n", n - sum);
    }
}
