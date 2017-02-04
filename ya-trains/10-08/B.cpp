#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

const int N = 4e5 + 123;

ll getsum(int l, int r, const vector<ll>& a) {
    return a[r] - a[l - 1];
}

int main() {
#if __APPLE__
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif

    int n;
    scanf("%d", &n);

    vector<ll> a(N), b(N), x(n);
    for (int i = 0; i < n; ++i) {
        scanf("%lld", &x[i]);
        ++a[x[i]];
    }

    for (int i = 0; i < N; i++) {
        b[i] = a[i] * i;
    }

    vector<ll> suma(N), sumb(N);
    partial_sum(a.begin(), a.end(), suma.begin());
    partial_sum(b.begin(), b.end(), sumb.begin());

    sort(x.begin(), x.end());
    x.erase(unique(x.begin(), x.end()), x.end());

    ll ans = 0;
    for (int i = 0; i < x.size(); ++i) {
        ll cur = getsum(x[i], N - 1, sumb);
        for (int y = x[i]; y + x[i] < N; y += x[i]) {
            cur -= getsum(y, y + x[i] - 1, sumb) - y * getsum(y, y + x[i] - 1, suma);
        }
        ans = max(ans, cur);
    }
    printf("%lld\n", ans);
}
