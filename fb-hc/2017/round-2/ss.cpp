#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    freopen("ss.in", "r", stdin);
    freopen("ss.out", "w", stdout);

    int t;
    scanf("%d", &t);

    for (int test = 1; test <= t; ++test) {
        ll n, m, k;
        scanf("%lld%lld%lld", &n, &m, &k);

        if (n > m) swap(n, m);
        ll s = (n + k - 1) / k;
        if (2 * k + 1 <= n) {
            s = min(s, 4ll + (k == 1));
        }
        if (2 * k + 3 > m) s = -1;
        printf("Case #%d: %lld\n", test, s);
    }
}
