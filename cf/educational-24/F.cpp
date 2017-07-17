#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

#if __APPLE__
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define eprintf(...)
#endif

ll f(ll n, ll k) {
    ll v = n - k;
    ll bridge = k;
    ll ret = bridge + min(bridge, v * (v - 1) / 2);
    return ret;
}

void solve(int n) {
    eprintf("n = %d\n", n);
    ll lb = 0, rb = n - 1;
    while (lb + 2 < rb) {
        ll mb1 = (lb + lb + rb) / 3;
        ll mb2 = (lb + rb + rb) / 3;
        if (f(n, mb1) > f(n, mb2)) {
            rb = mb2;
        } else {
            lb = mb1;
        }
    }
    ll ans = f(n, lb);
    for (int i = lb + 1; i <= rb; ++i) {
        eprintf("k = %d, f = %lld\n", i, f(n, i));
        ans = max(ans, f(n, i));
    }
    printf("%lld\n", ans);
}

int main() {
#if __APPLE__
    freopen("F.in", "r", stdin);
    freopen("F.out", "w", stdout);
#endif

    int q;
    while (scanf("%d", &q) == 1) {
        for (int i = 0; i < q; ++i) {
            int n;
            scanf("%d", &n);
            solve(n);
        }
    }
}
