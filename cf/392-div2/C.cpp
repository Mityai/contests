#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

int main() {
#if __APPLE__
    //freopen("C.in", "r", stdin);
    //freopen("C.out", "w", stdout);
#endif

    ll n, m, k, x, y;
    while (cin >> n >> m >> k >> x >> y) {
    --x, --y;

    ll most = 0, less = 1e18, he = 0;
    if (n == 1) {
        ll cnt = k / m;
        ll rest = k % m;
        less = cnt;
        most = cnt;
        he = cnt;
        if (rest > 0) {
            ++most;
            if (y < rest) {
                ++he;
            }
        }
    } else {
        ll one = n * m + (n - 2) * m;
        ll cnt = k / one;
        ll rest = k % one;
        vector<vector<ll>> a(n, vector<ll>(m));
        for (int i = 0; i < m; ++i) {
            a[0][i] = cnt;
            a[n - 1][i] = cnt;
        }
        for (int i = 1; i < n - 1; ++i) {
            for (int j = 0; j < m; ++j) {
                a[i][j] = cnt * 2;
            }
        }

        for (int i = 0; i < n; ++i) {
            if (rest == 0) break;
            for (int j = 0; j < m; ++j) {
                ++a[i][j];
                --rest;
                if (rest == 0) break;
            }
        }
        for (int i = n - 2; i >= 0; --i) {
            if (rest == 0) break;
            for (int j = 0; j < m; ++j) {
                ++a[i][j];
                --rest;
                if (rest == 0) break;
            }
        }
        most = 0;
        less = 1e18;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                most = max(most, a[i][j]);
                less = min(less, a[i][j]);
            }
        }
        he = a[x][y];
    }

    cout << most << ' ' << less << ' ' << he << endl;
    }
}
