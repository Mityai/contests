#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

int main() {
#if __APPLE__
    freopen("D.in", "r", stdin);
    freopen("D.out", "w", stdout);
#endif

    int n, l, r;
    while (scanf("%d%d%d", &n, &l, &r) == 3) {
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            scanf("%d", &a[i]);
        }
        vector<int> c(n);
        for (int i = 0; i < n; ++i) {
            scanf("%d", &c[i]);
        }
        vector<int> b(n);
        int mx = a[0] + c[0];
        for (int i = 0; i < n; ++i) {
            b[i] = a[i] + c[i];
            mx = max(mx, b[i]);
        }

        if (mx > r) {
            int del = mx - r;
            for (int i = 0; i < n; ++i) {
                b[i] -= del;
            }
        }
        int mn = b[0];
        for (int i = 0; i < n; ++i) {
            mn = min(mn, b[i]);
        }                 
        if (mn < l) {
            int add = l - mn;
            for (int i = 0; i < n; ++i) {
                b[i] += add;
            }
        }

        bool ok = true;
        for (int i = 0; i < n; ++i) {
            if (b[i] < l || b[i] > r) {
                ok = false;
                break;
            }
        }

        if (ok) {
            for (int x : b) {
                printf("%d ", x);
            }
            puts("");
        } else {
            puts("-1");
        }
    }
}
