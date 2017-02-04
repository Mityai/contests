#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

ll dist(pair<ll, ll> pt1, pair<ll, ll> pt2) {
    return (pt1.fi - pt2.fi) * (pt1.fi - pt2.fi) + (pt1.se - pt2.se) * (pt1.se - pt2.se);
}

int main() {
    ll n, x1, y1, x2, y2;
    cin >> n >> x1 >> y1 >> x2 >> y2;

    vector< pair<ll, ll> > pts(n);
    for (int i = 0; i < n; i++) {
        cin >> pts[i].fi >> pts[i].se;
    }

    ll ans = LLONG_MAX;
    for (int i = 0; i < n; i++) {
        ll r1 = dist(pts[i], {x1, y1});
        ll r2 = 0;
        for (int j = 0; j < n; j++) {
            if (dist(pts[j], {x1, y1}) > r1) {
                r2 = max(r2, dist(pts[j], {x2, y2}));
            }
        }
        if (r1 + r2 < ans) {
            ans = r1 + r2;
        }
    }
    for (int i = 0; i < n; i++) {
        ll r1 = dist(pts[i], {x2, y2});
        ll r2 = 0;
        for (int j = 0; j < n; j++) {
            if (dist(pts[j], {x2, y2}) > r1) {
                r2 = max(r2, dist(pts[j], {x1, y1}));
            }
        }
        if (r1 + r2 < ans) {
            ans = r1 + r2;
        }
    }

    cout << ans << endl;
}
