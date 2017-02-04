#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

void solve() {
    int n, D;
    scanf("%d%d", &n, &D);

    vector< pair<int, int> > a(n);
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &a[i].fi, &a[i].se);
    }

    sort(a.begin(), a.end());
    for (int k = 0; k < n; k++) {
        int l = a[k].fi;
        int r = l + D;
        int mx = l;
        for (int i = 0; i < n; i++) {
            if (l <= a[i].fi && a[i].fi <= mx && a[i].se <= r) {
                mx = max(mx, a[i].se);
            }
        }
        if (mx == r) {
            puts("Yes");
            return;
        }
    }
    puts("No");
}

int main() {
    int t;
    scanf("%d", &t);

    for (int i = 0; i < t; i++) {
        solve();
    }
}
