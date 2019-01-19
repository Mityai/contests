#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
#if __APPLE__
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
#endif

    int n;
    scanf("%d", &n);

    vector<ll> b(n);
    for (int i = 0; i < n; ++i) {
        scanf("%lld", &b[i]);
    }

    if (n == 1) {
        puts("0");
        return 0;
    }

    const int inf = n * 10;
    int best = inf;
    auto a = b;
    for (a[0] = b[0] - 1; a[0] <= b[0] + 1; ++a[0]) {
        for (a[1] = b[1] - 1; a[1] <= b[1] + 1; ++a[1]) {
            ll diff = a[1] - a[0];
            int curans = abs(a[0] - b[0]) + abs(a[1] - b[1]);
            bool ok = true;
            for (int j = 2; j < n; ++j) {
                ll need = a[j - 1] + diff;
                if (abs(need - b[j]) <= 1) {
                    a[j] = need;
                    curans += abs(need - b[j]);
                } else {
                    ok = false;
                }
            }
            if (ok) {
                best = min(best, curans);
            }
        }
    }

    if (best == inf) {
        puts("-1");
    } else {
        printf("%d\n", best);
    }
}
