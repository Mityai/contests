#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

const int INF = 1234567890;

int main() {
    freopen("segments.dat", "r", stdin);
    freopen("segments.sol", "w", stdout);

    int n;
    while (scanf("%d", &n) == 1) {
        vector< pair<int, int> > a(n);
        int C = 50;
        int c[max(n, C) + 1];
        memset(c, 0, sizeof c);
        for (int i = 0; i < n; i++) {
            scanf("%d%d", &a[i].fi, &a[i].se);
            c[a[i].se] = a[i].fi;
        }

        int ans = INF;
        for (int i = 1; i <= C; i++) {
            for (int j = 1; j < i; j++) {
                for (int k = 1; k < j; k++) {
                    int b[3] = {c[i], c[j], c[k]};
                    sort(b, b + 3);
                    if (b[2] < b[0] + b[1]) {
                        ans = min(ans, i + j + k);
                    }
                }
            }
        }
        if (ans == INF) {
            puts("-1");
        } else {
            printf("%d\n", ans);
        }
    }
}
