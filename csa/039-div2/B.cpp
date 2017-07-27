#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

#if __APPLE__
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define eprintf(...)
#endif

typedef long long ll;

int n;

int dist(int i, int j) {
    if (i < j) swap(i, j);
    return min(i - j, n - i + j);
}

int main() {
    scanf("%d", &n);

    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i].fi);
        a[i].se = i;
    }

    sort(a.begin(), a.end());

    ll ans = 0;
    for (int i = 1; i < n; ++i) {
        ans += dist(a[i - 1].se, a[i].se);
    }
    printf("%lld\n", ans);
}
