#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    int n;
    ll w;
    scanf("%d%lld", &n, &w);

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }

    ll curval = 0;
    ll minval = 0;
    ll maxval = 0;
    for (int i = 0; i < n; ++i) {
        curval += a[i];
        minval = min(minval, curval);
        maxval = max(maxval, curval);
    }

    ll ans = max(0ll, w - (maxval - minval) + 1);
    printf("%lld\n", ans);
}
