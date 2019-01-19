#include <bits/stdc++.h>
using namespace std;

#if __APPLE__
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define eprintf(...)
#endif

using ll = long long;

int main() {
#if __APPLE__
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
#endif

    int n, m;
    scanf("%d%d", &n, &m);

    vector<ll> a(n);
    for (int i = 0; i < n; ++i) {
        scanf("%lld", &a[i]);
    }

    ll sum = 0;
    for (int i = 0, j = 0; i < m; ++i) {
        ll b;
        scanf("%lld", &b);

        while (j < n && sum + a[j] < b) {
            sum += a[j];
            ++j;
        }

        printf("%d %lld\n", j + 1, b - sum);
    }
}
