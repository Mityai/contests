#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

struct F {
    char c;
    int x, y;
};

const int INF = 1234567890;

int main() {
#if __APPLE__
    freopen("D.in", "r", stdin);
    freopen("D.out", "w", stdout);
#endif

    int n;
    scanf("%d", &n);

    int x0, y0;
    scanf("%d%d", &x0, &y0);

    vector<F> f(n);
    F left, right, up, down, lu, ru, ld, rd;
    left.x = -INF;
    right.x = INF;
    up.y = INF;
    down.y = -INF;
    lu.x = -INF;
    ld.x = -INF;
    rd.x = INF;
    ru.x = INF;
    for (int i = 0; i < n; i++) {
        scanf(" %c%d%d", &f[i].c, &f[i].x, &f[i].y);
        //if (i == 0) left = right = up = down = lu = ru = ld = rd = f[i];
        if (f[i].x == x0) {
            if (f[i].y < y0) {
                if (f[i].y > down.y) {
                    down = f[i];
                }
            } else {
                if (f[i].y < up.y) {
                    up = f[i];
                }
            }
        }
        if (f[i].y == y0) {
            if (f[i].x < x0) {
                if (f[i].x > left.x) {
                    left = f[i];
                }
            } else {
                if (f[i].x < right.x) {
                    right = f[i];
                }
            }
        }
        if (-x0 + y0 == -f[i].x + f[i].y) {
            if (f[i].x < x0) {
                if (f[i].x > lu.x) {
                    lu = f[i];
                }
            } else if (f[i].x > x0) {
                if (f[i].x < rd.x) {
                    rd = f[i];
                }
            }
        }
        if (x0 + y0 == f[i].x + f[i].y) {
            if (f[i].x < x0) {
                if (f[i].x > ld.x) {
                    ld = f[i];
                }
            } else if (f[i].x > x0) {
                if (f[i].x < ru.x) {
                    ru = f[i];
                }
            }
        }
    }

    bool ans = false;
    if (up.x == x0 && up.c != 'B') ans = true;
    if (down.x == x0 && down.c != 'B') ans = true;
    if (left.y == y0 && left.c != 'B') ans = true;
    if (right.y == y0 && right.c != 'B') ans = true;
    if (ld.x + ld.y == x0 + y0 && ld.c != 'R') ans = true;
    if (-lu.x + lu.y == -x0 + y0 && lu.c != 'R') ans = true;
    if (-rd.x + rd.y == -x0 + y0 && rd.c != 'R') ans = true;
    if (ru.x + ru.y == x0 + y0 && ru.c != 'R') ans = true;

    if (ans) cout << "YES" << endl;
    else cout << "NO" << endl;
}
