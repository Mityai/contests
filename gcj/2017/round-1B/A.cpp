#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

int main() {
#if __APPLE__
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
#endif

    int t;
    scanf("%d", &t);

    for (int test = 1; test <= t; ++test) {
        double d;
        int n;
        scanf("%lf%d", &d, &n);

        vector<pair<double, double>> a(n);
        for (int i = 0; i < n; ++i) {
            scanf("%lf%lf", &a[i].fi, &a[i].se);
        }

        sort(a.rbegin(), a.rend());

        double t = 0;
        for (int i = 0; i < n; ++i) {
            t = max(t, (d - a[i].fi) / a[i].se);
        }
        double ans = d / t;
        printf("Case #%d: %.10lf\n", test, ans);
    }
}
