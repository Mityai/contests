#include <bits/stdc++.h>
#define x first
#define y second
#define fi first
#define se second
using namespace std;

const int N = 200;

int n;
vector< pair<int, int> > a;
int len[N];
int sumlen;

const int D[] = {-1, 1};

int dist(int i, int j) {
    return abs(a[i].fi - a[j].fi) + abs(a[i].se - a[j].se);
}

int minlen(int i) {
    return min(sumlen - len[i], len[i]);
}

bool rotation(int prev, int cur, int nxt) {
    if (a[prev].y < a[cur].y && a[nxt].x < a[cur].x) return true;
    if (a[cur].x < a[prev].x && a[nxt].y < a[cur].y) return true;
    if (a[cur].y < a[prev].y && a[nxt].x > a[cur].x) return true;
    if (a[cur].x > a[prev].x && a[nxt].y > a[cur].y) return true;
    return false;
}

int f(int i, int j) {
    return (i + j + n) % n;
}

int main() {
#if __APPLE__
    freopen("D.in", "r", stdin);
    freopen("D.out", "w", stdout);
#endif

    scanf("%d", &n);

    a.resize(n);
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &a[i].fi, &a[i].se);
    }

    len[0] = 0;
    for (int i = 1; i < n; i++) {
        len[i] = len[i - 1] + dist(i, i - 1);
    }
    sumlen = len[n - 1] + dist(0, n - 1);

    int mx1 = 0, mx2 = 0;
    for (int i = 1; i < n; i++) {
        if (rotation(f(i, -1), i, f(i, 1)) == 0) {
            mx1 = max(mx1, len[i]);
        } else {
            mx2 = max(mx2, sumlen - len[i]);
        }
    }

    int ans = 0;

    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            int dv, du;
            if (rotation(f(i, -1), i, f(i, 1)) == 0) {
                if (mx1 < mx2) dv = du = -1;
                else dv = du = 1;
            } else {
                if (mx1 < mx2) dv = du = 1;
                else dv = du = -1;
            }
            int v = i, u = j;
            int cur = 0;
            while (true) {
                if (v == 0 || u == 0) break;
                if (rotation(f(v, -dv), v, f(v, dv)) !=
                    rotation(f(u, -du), u, f(u, du))) {
                    break;
                }
                cur += dist(v, f(v, dv));
                v = f(v, dv);
                u = f(u, du);
                if (dist(v, f(v, -dv)) != dist(u, f(u, -du))) {
                    break;
                }
            }
            cur += minlen(v);
            ans = max(ans, cur - minlen(i));
        }
    }

    printf("%d\n", ans);
}
