#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

int main() {
#if __APPLE__
    //freopen("D.in", "r", stdin);
    //freopen("D.out", "w", stdout);
#endif

    int n;
    while (cin >> n) {

    string s;
    cin >> s;

    reverse(s.begin(), s.end());
    int m = s.length();

    ll ans = 0;
    ll p = 1;
    int i = 0;
    while (i < m) {
        int mx = 1;
        ll num = 0;
        ll ten = 1;
        for (int j = 0; j < 11 && i + j < m; ++j) {
            num += ten * (s[i + j] - '0');
            ten *= 10;
            if (num < n && s[i + j] != '0') {
                mx = max(mx, j + 1);
            }
        }
        num = 0;
        ten = 1;
        for (int j = 0; j < mx; ++j) {
            num += ten * (s[i + j] - '0');
            ten *= 10;
        }
        ans += num * p;
        p *= n;
        i += mx;
    }

    cout << ans << endl;
}
}
