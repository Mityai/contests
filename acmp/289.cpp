#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll MAX = ll(1e15) + 1;

bool prime(ll x) {
    if (x == 2) return true;
    if (x == 1 || x % 2 == 0) return false;
    for (ll i = 3; i * i <= x; i += 2) {
        if (x % i == 0) return false;
    }
    return true;
}

int main() {
    ll d;
    while (scanf("%lld", &d) == 1) {
        if (d == 1) {
            puts("1");
            continue;
        }

        vector<int> dels;
        for (ll p = 2; p * p <= d; p++) {
            while (d % p == 0) {
                dels.push_back(p - 1);
                d /= p;
            }
        }
        if (d != 1) {
            dels.push_back(d - 1);
        }
        reverse(dels.begin(), dels.end());

        ll ans = 1;
        bool ok = true;
        for (ll p = 2, i = 0; i < (int)dels.size(); p++) {
            if (prime(p)) {
                printf("%lld^%d\n", p, dels[i]);
                for (int j = 0; j < dels[i]; j++) {
                    ans *= p;
                    if (ans > MAX) {
                        puts("0");
                        ok = false;
                        break;
                    }
                }
                if (!ok) break;
                i++;
            }
        }
        if (ok) printf("%lld\n", ans);
    }
}
