#include <bits/stdc++.h> 
#define fi first
#define se second
using namespace std;

using ll = long long;

int main() {
#if __APPLE__
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
#endif

    int n, d;
    scanf("%d%d", &n, &d);

    vector< pair<int, int> > x(n);
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &x[i].fi, &x[i].se);
    }

    vector< pair<int, int> > mx(n);

    mx[n - 1] = {x[n - 1].se, n - 1};
    for (int i = n - 2; i >= 0; i--) {
        mx[i] = mx[i + 1];
        if (x[i].se > mx[i].fi) {
            mx[i] = {x[i].se, i};
        }
    }

    int ansi = -1, ansj = -1;
    for (int i = 0, j = 1; i < n; i++) {
        while (j < n && x[j].fi - x[i].fi < d) {
            j++;
        }
        if (j < n && x[j].fi - x[i].fi >= d) {
            if (ansi == -1 || x[i].se + mx[j].fi > x[ansi].se + x[ansj].se) {
                ansi = i;
                ansj = mx[j].se;
            }
        }
    }

    if (ansi == -1) {
        puts("-1 -1");
    } else {
        printf("%d %d\n", ansi + 1, ansj + 1);
    }
}
