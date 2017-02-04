#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

int getlen(ll x) {
    if (x == 0) return 1;
    int cnt = 0;
    while (x > 0) {
        ++cnt;
        x /= 10;
    }
    return cnt;
}

ll ten(ll x) {
    ll ret = 1;
    for (int i = 0; i != x; ++i) {
        ret *= 10LL;
    }
    return ret;
}

int main() {
#if __APPLE__
    freopen("6.in", "r", stdin);
    freopen("6.out", "w", stdout);
#else
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int n;
    scanf("%d", &n);

    vector<int> rest(7);
    vector<int> a(n);
    for (int i = 0; i != n; ++i) {
        scanf("%d", &a[i]);
        ++rest[a[i] % 7];
    }

    ll ans = 0;
    for (int i = 0; i != n; ++i) {
        for (int r = 0; r != 7; ++r) {
            if ((r * (ten(getlen(a[i])) % 7) + a[i]) % 7 == 0) {
                ans += rest[r];
            }
        }
        if (((a[i] % 7) * (ten(getlen(a[i])) % 7) + a[i]) % 7 == 0) {
            ans--;
        }
    }

    printf("%lld\n", ans);
}
