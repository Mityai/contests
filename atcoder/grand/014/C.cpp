#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

const int N = 800 + 2;
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

char a[N][N];
int d[N][N][N / 2 + 1];
int h, w, k;
int mind;

bool in(int i, int j) {
    return 0 <= i && i < h && 0 <= j && j < w;
}

queue<pair<pair<int, int>, int>> q;

void go(int i, int j, int free, int locked, int newdist) {
    for (int t = 0; t < 4; ++t) {
        int newi = i + dx[t];
        int newj = j + dy[t];
        if (in(newi, newj)) {
            if (a[newi][newj] == '#') {
                if (k * (newdist - 1) - locked > 0) {
                   if (d[newi][newj][locked + 1] > newdist) {
                       d[newi][newj][locked + 1] = newdist;
                       q.push({{newi, newj}, locked + 1});
                       if (free - 1 > 0) {
                           go(newi, newj, free - 1, locked + 1, newdist);
                       }
                   }
                }
            } else {
                if (d[newi][newj][locked] > newdist) {
                    d[newi][newj][locked] = newdist;
                    q.push({{newi, newj}, locked});
                    if (free - 1 > 0) {
                        go(newi, newj, free - 1, locked, newdist);
                    }
                }
            }
        }
    }
}

int main() {
#if __APPLE__
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif

    scanf("%d%d%d", &h, &w, &k);

    int si, sj;
    for (int i = 0; i < h; ++i) {
        scanf(" %s", a[i]);
        for (int j = 0; j < w; ++j) {
            if (a[i][j] == 'S') {
                si = i;
                sj = j;
                a[i][j] = '.';
            }
        }
    }

    mind = min({si, sj, h - si - 1, w - sj - 1});

    memset(d, 127, sizeof d);
    const int INF = d[0][0][0];

    for (int i = 0; i <= mind; ++i) {
        d[si][sj][0] = i;
        q.push({{si, sj}, 0});

        while (!q.empty()) {
            int vi = q.front().fi.fi;
            int vj = q.front().fi.se;
            int locked = q.front().se;
            q.pop();

            if (vi == 0 || vi == h - 1 || vj == 0 || vj == w - 1) break;

            go(vi, vj, k, locked, d[vi][vj][locked] + 1);
        }
        while (!q.empty()) {
            q.pop();
        }
    }

    int ans = INF;
    for (int i = 0; i < h; ++i) {
        for (int t = 0; t <= mind; ++t) {
            ans = min(ans, d[i][0][t]);
            ans = min(ans, d[i][w - 1][t]);
        }
    }
    for (int i = 0; i < w; ++i) {
        for (int t = 0; t <= mind; ++t) {
            ans = min(ans, d[0][i][t]);
            ans = min(ans, d[h - 1][i][t]);
        }
    }

    printf("%d\n", ans);
}
