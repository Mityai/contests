#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

struct Eve {
    int x, id;
};

bool cmp(Eve e1, Eve e2) {
    return e1.x < e2.x;
}

int main() {
#if __APPLE__
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif

    int n, m;
    while (scanf("%d%d", &n, &m) == 2) {
        int a[n], p[n];
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
            --a[i];
            p[a[i]] = i;
        }

        vector< pair<int, int> > q(m);
        vector<Eve> op, cl;
        for (int i = 0; i < m; i++) {
            int x, y;
            scanf("%d%d", &x, &y);
            --x, --y;
            q[i].fi = min(p[x], p[y]);
            q[i].se = max(p[x], p[y]);
            op.push_back({q[i].fi, i});
            cl.push_back({q[i].se, i});
        }

        sort(op.begin(), op.end(), cmp);
        sort(cl.begin(), cl.end(), cmp);
        ll ans = 0;
        bool opened[n];
        memset(opened, 0, sizeof opened);
        for (int i = 0, j = 0, k = 0; i < n; i++) {
            while (k < (int)cl.size() && cl[k].x < i) k++;
            while (k < (int)cl.size() && cl[k].x == i) {
                j = max(j, q[cl[k].id].fi + 1);
                k++;
            }
            ans += i - j + 1;
        }

        printf("%lld\n", ans);
    }
}
