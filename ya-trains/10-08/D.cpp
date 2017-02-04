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

    int n, k, d;
    scanf("%d%d%d", &n, &k, &d);

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }

    sort(a.begin(), a.end());

    int lb = 0, rb = n + 1;
    while (lb + 1 < rb) {
        int mb = (lb + rb) / 2;
        vector<int> p(n);
        for (int i = 0; i < mb; ++i) {
            p[i] = a[i];
        }
        int uk = mb;
        bool ok = true;
        for (int j = 0; j < k - 1; ++j) {
            for (int i = 0; i < mb; ++i) {
                while (uk < n && p[i] + d > a[uk]) {
                    ++uk;
                }
                if (uk < n && p[i] + d <= a[uk]) {
                    p[i] = a[uk];
                    ++uk;
                } else {
                    ok = false;
                }
                if (!ok) break;
            }
            if (!ok) break;
        }
        if (ok) {
            lb = mb;
        } else {
            rb = mb;
        }
    }
    printf("%d\n", lb);
}
