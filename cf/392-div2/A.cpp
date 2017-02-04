#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

int main() {
#if __APPLE__
    //freopen("A.in", "r", stdin);
    //freopen("A.out", "w", stdout);
#endif

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    int mx = a[0];
    for (int i = 1; i < n; ++i) {
        mx = max(mx, a[i]);
    }

    ll ans = 0;
    for (int i = 0; i < n; ++i) {
        ans += mx - a[i];
    }

    cout << ans << endl;
}
