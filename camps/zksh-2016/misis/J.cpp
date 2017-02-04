#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

const int INF = 1234567890;

struct Q {
    int x, y1, y2, val;
};

bool cmp(Q q1, Q q2) {
    return q1.x < q2.x;
}

int main() {
#if __APPLE__
    freopen("J.in", "r", stdin);
    freopen("J.out", "w", stdout);
#endif

    int q;
    scanf("%d", &q);

    vector<Q> ev(q + q);
    set<int> xs;
    for (int i = 0; i < q; i++) {
        int x1, y1, x2, y2, val;
        scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &val);

        xs.insert(x1 - 1);
        xs.insert(x1);
        xs.insert(x2 + 1);
        ev[i] = {x1, y1, y2, val};
        ev[i + q] = {x2 + 1, y1, y2, -val};
    }

    int n, m;
    scanf("%d%d", &n, &m);

    int a[m + 1];
    memset(a, 0, sizeof a);

    sort(ev.begin(), ev.end(), cmp);

    int i = 0;
    int ans = -INF;
    for (auto x : xs) {
        while (i < (int)ev.size() && ev[i].x < x) i++;

        while (i < (int)ev.size() && ev[i].x == x) {
            int y1 = ev[i].y1, y2 = ev[i].y2;
            for (int y = y1; y <= y2; y++) a[y] += ev[i].val;
            i++;
        }

        if (1 <= x && x <= n) {
            for (int i = 1; i <= m; i++) {
                ans = max(ans, a[i]);
            }
        }
    }

    printf("%d\n", ans);
}
