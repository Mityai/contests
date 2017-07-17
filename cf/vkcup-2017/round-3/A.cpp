#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

int main() {
#if __APPLE__
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
#endif

    int t;
    scanf("%d", &t);

    for (int it = 0; it < t; ++it) {
        ll x, y, p, q;
        scanf("%lld%lld%lld%lld", &x, &y, &p, &q);

        if (p == 1 && q == 1) {
            if (x != y) {
                puts("-1");
            } else {
                puts("0");
            }
            continue;
        }

        if (p == 0) {
            if (x == 0) {
                puts("0");
            } else {
                puts("-1");
            }
            continue;
        }

        ll ans = max({(y + q - 1) / q, (x + p - 1) / p, (y - x + q - p - 1) / (q - p)});
        printf("%lld\n", ans * q - y);
    }
}
