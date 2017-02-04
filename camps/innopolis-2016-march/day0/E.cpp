#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    freopen("missions.in", "r", stdin);
    freopen("missions.out", "w", stdout);

    int n;
    scanf("%d", &n);

    int a[n], b[n];
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &a[i], &b[i]);
    }

    int maxa = 0, maxb = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] > a[maxa]) maxa = i;
        if (b[i] > b[maxb]) maxb = i;
    }

    if (maxa == maxb) {
        ll ans = a[maxa] + b[maxb];
        printf("%lld\n", ans);
        printf("%d ", maxa + 1);

        for (int i = 0; i < n; i++) {
            if (i != maxa) {
                printf("%d ", i + 1);
            }
        }
        puts("");
    } else {
        ll ans = a[maxa] + b[maxb];
        if (b[maxa] < a[maxb]) {
            ans += b[maxa];
            printf("%lld\n", ans);
            printf("%d %d ", maxa + 1, maxb + 1);
        } else {
            ans += a[maxb];
            printf("%lld\n", ans);
            printf("%d %d ", maxb + 1, maxa + 1);
        }

        for (int i = 0; i < n; i++) {
            if (i != maxa && i != maxb) {
                printf("%d ", i + 1);
            }
        }
        puts("");
    }
}
