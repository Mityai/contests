#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

int main() {
#if __APPLE__
    //freopen("B.in", "r", stdin);
    //freopen("B.out", "w", stdout);
#endif

    int m, b;
    scanf("%d%d", &m, &b);

    ll ans = 0;
    for (int y = 0; y <= b; ++y) {
        int x = m * (b - y);

        ll xs = x * 1ll * (x + 1) / 2;
        ll ys = y * 1ll * (y + 1) / 2;
        xs *= (y + 1);
        ys *= (x + 1);
        ans = max(ans, xs + ys);
    }

    printf("%lld\n", ans);
}
