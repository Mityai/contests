#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

ll hor(ll h, ll w) {
    ll x = h / 3;
    ll mx = x + (h % 3 != 0);
    ll mn = x;
    return w * (mx - mn);
}

pair<ll, ll> divv(ll h, ll w) {
    ll x = h / 2;
    ll mn = x;
    ll mx = x + h % 2;
    return {mn * w, mx * w};
}

int main() {
#if __APPLE__
    //freopen("A.in", "r", stdin);
    //freopen("A.out", "w", stdout);
#endif

    ll h, w;
    cin >> h >> w;

    ll ans = min(hor(h, w), hor(w, h));
    for (int i = 1; i < h; ++i) {
        ll area = (h - i) * w;
        auto v = divv(w, i);
        ll mn = min({area, v.fi, v.se});
        ll mx = max({area, v.fi, v.se});
        ans = min(ans, mx - mn);
    }
    for (int i = 1; i < w; ++i) {
        ll area = (w - i) * h;
        auto v = divv(h, i);
        ll mn = min({area, v.fi, v.se});
        ll mx = max({area, v.fi, v.se});
        ans = min(ans, mx - mn);
    }

    printf("%lld\n", ans);
}
