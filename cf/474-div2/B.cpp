#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
#if __APPLE__
    // freopen("B.in", "r", stdin);
    // freopen("B.out", "w", stdout);
#endif

    int n, k1, k2;
    scanf("%d%d%d", &n, &k1, &k2);

    int sumk = k1 + k2;

    vector<int> a(n), b(n);
    for (int& x : a) scanf("%d", &x);
    for (int& x : b) scanf("%d", &x);

    vector<int> c(n);
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        c[i] = abs(a[i] - b[i]);
        sum += c[i];
    }

    ll ans = 0;
    if (sum > sumk) {
        int lb = -1, rb = 2e6;
        while (lb + 1 < rb) {
            int mb = (lb + rb) / 2;
            int need = 0;
            for (int i = 0; i < n; ++i) {
                need += max(0, c[i] - mb);
            }
            if (need <= sumk) {
                rb = mb;
            } else {
                lb = mb;
            }
        }
        int left = k1 + k2;
        for (int i = 0; i < n; ++i) {
            int val = min(rb, c[i]);
            left -= c[i] - val;
            c[i] = val;
        }
        sort(c.rbegin(), c.rend());
        for (int i = 0; i < left; ++i) {
            --c[i];
        }
        for (int i = 0; i < n; ++i) {
            ans += c[i] * 1ll * c[i];
        }
    } else {
        int left = sumk - sum;
        ans = left & 1;
    }

    printf("%lld\n", ans);
}
