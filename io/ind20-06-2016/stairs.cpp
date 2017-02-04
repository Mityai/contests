#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int getmin(int x, int y, int n) {
    if (x > y) swap(x, y);
    return min(y - x, n - y + x);
}

int main() {
    freopen("stairs.in", "r", stdin);
    freopen("stairs.out", "w", stdout);

    int n, m;
    while (scanf("%d%d", &n, &m) == 2) {
        set<int> q;
        for (int i = 0; i < n; i++) {
            q.insert(i + 1);
        }

        for (int i = 0; i < m; i++) {
            int t;
            scanf("%d", &t);

            if (t == 1) {
                int x;
                scanf("%d", &x);
                q.erase(x);
            } else {
                int x, y;
                scanf("%d%d", &x, &y);

                int ans = INF;

                auto c = q.lower_bound(x);
                auto l = c; if (c != q.begin()) l--;
                auto r = q.upper_bound(x);
                auto b = q.begin();
                auto e = --q.end();

                if (l != q.end()) {
                    ans = min(ans, getmin(*l, x, n) + getmin(*l, y, n));
                }
                if (c != q.end()) {
                    ans = min(ans, getmin(*c, x, n) + getmin(*c, y, n));
                }
                if (r != q.end()) {
                    ans = min(ans, getmin(*r, x, n) + getmin(*r, y, n));
                }
                if (b != q.end()) {
                    ans = min(ans, getmin(*b, x, n) + getmin(*b, y, n));
                }
                if (e != q.end()) {
                    ans = min(ans, getmin(*e, x, n) + getmin(*e, y, n));
                }

                assert(ans != INF);
                printf("%d\n", ans);
            }
        }
    }
}
