#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

int main() {
#if __APPLE__
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif

    int n;
    scanf("%d", &n);

    bool one = false, two = false;
    vector<int> cur(n + 1);
    vector<pair<int, int>> q(n);
    int maxdiv2 = -1;
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &q[i].fi, &q[i].se);

        if (q[i].se == 2 && (maxdiv2 == -1 || cur[i] > cur[maxdiv2])) {
            maxdiv2 = i;
        }
        cur[i + 1] = cur[i] + q[i].fi;
        if (q[i].se == 1) {
            one = true;
        } else {
            two = true;
        }
    }

    if (!one) {
        int ans = 1899;
        for (int i = maxdiv2; i < n; i++) {
            ans += q[i].fi;
        }
        cout << ans << endl;
        return 0;
    }

    if (!two) {
        puts("Infinity");
        return 0;
    }

    for (int i = 0; i < n; i++) {
        if (q[i].se == 1 && cur[i] <= cur[maxdiv2]) {
            puts("Impossible");
            return 0;
        }
    }

    int maxdiff = cur[n] - cur[maxdiv2];
    cout << maxdiff + 1899 << endl;
}
