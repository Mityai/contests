#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

const int INF = 1234567890;

struct Ant {
    int x, y, dx, dy, i;
};

int dist(Ant a, Ant b) {
    if (a.x == b.x && a.y == b.y) return 0;
    if (a.dx - b.dx != 0) {
        int t = (b.x - a.x) / (a.dx - b.dx);
        if (t >= 0 && t * (a.dy - b.dy) == b.y - a.y) {
            return abs(a.x - b.x) + abs(a.y - b.y);
        }
    } else if (a.dy - b.dy != 0) {
        int t = (b.y - a.y) / (a.dy - b.dy);
        if (t >= 0 && t * (a.dx - b.dx) == b.x - a.x) {
            return abs(a.y - b.y) + abs(a.x - b.x);
        }
    }
    return INF;
}

bool cmp(pair< int, pair<Ant, Ant> > a, pair< int, pair<Ant, Ant> > b) {
    return a.fi < b.fi;
}

int main() {
#if __APPLE__
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
#endif

    int n;
    while (scanf("%d", &n) == 1) {

        vector<Ant> a(n);
        for (int i = 0; i < n; i++) {
            char c;
            scanf("%d%d %c", &a[i].x, &a[i].y, &c);
            a[i].x *= 2;
            a[i].y *= 2;
            if (c == 'N') a[i].dx = 0, a[i].dy = 1;
            if (c == 'E') a[i].dx = 1, a[i].dy = 0;
            if (c == 'S') a[i].dx = 0, a[i].dy = -1;
            if (c == 'W') a[i].dx = -1, a[i].dy = 0;
            a[i].i = i;
        }

        int ds[n][n];
        vector< pair< int, pair<Ant, Ant> > > q;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    int d = dist(a[i], a[j]);
                    ds[i][j] = d;
                    if (d != INF) {
                        q.push_back({d, {a[i], a[j]}});
                    }
                }
            }
        }

        sort(q.begin(), q.end(), cmp);

        bool del[n];
        memset(del, 0, sizeof del);
        int tm[n];
        memset(tm, -1, sizeof tm);

        for (int i = 0; i < (int)q.size(); i++) {
            auto A = q[i].se.fi;
            auto B = q[i].se.se;
            if (del[A.i] && del[B.i]) {
                continue;
            } else if (del[A.i] && tm[A.i] == ds[A.i][B.i]) {
                del[B.i] = true;
                tm[B.i] = ds[A.i][B.i];
            } else if (del[B.i] && tm[B.i] == ds[B.i][A.i]) {
                del[A.i] = true;
                tm[A.i] = ds[B.i][A.i];
            } else if (!del[A.i] && !del[B.i]) {
                del[A.i] = del[B.i] = true;
                tm[A.i] = tm[B.i] = ds[A.i][B.i];
            }
        }

        int ans = 0;
        for (int i = 0; i < n; i++) {
            ans += !del[i];
        }

        printf("%d\n", ans);
    }
}
