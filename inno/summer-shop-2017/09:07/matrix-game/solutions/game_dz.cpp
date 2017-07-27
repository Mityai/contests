#include <bits/stdc++.h>
using namespace std;

const int N = 100;

int n, m;
int a[N + 1][N + 1];
int win[N + 1][N + 1];
int deg[N + 1][N + 1];

bool in(int x, int q) {
    return 1 <= x && x <= q;
}

int main() {
#if not __APPLE__
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
#endif

    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) {
        scanf("%d", &a[i][j]);
        win[i][j] = -1;
    }

    int si, sj;
    scanf("%d%d", &si, &sj);

    queue<pair<int, int>> q;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (!in(i + a[i][j], n) && !in(j + a[i][j], m)) {
                win[i][j] = 0;
                q.push({i, j});
            }
            deg[i][j] = in(i + a[i][j], n) + in(j + a[i][j], m);
        }
    }
    
    while (!q.empty()) {
        int vi = q.front().first;
        int vj = q.front().second;
        q.pop();

        for (int j = 1, i = vi; j <= m; ++j) {
            if (j == vj) continue;
            if (i == vi && j + a[i][j] == vj) {
                --deg[i][j];
                if (win[vi][vj] == 0) {
                    if (win[i][j] == -1) {
                        win[i][j] = 1;
                        q.push({i, j});
                    }
                } else {
                    if (deg[i][j] == 0 && win[i][j] == -1) {
                        win[i][j] = 0;
                        q.push({i, j});
                    }
                }
            }
        }
        for (int i = 1, j = vj; i <= n; ++i) {
            if (i == vi) continue;
            if (i + a[i][j] == vi && j == vj) {
                --deg[i][j];
                if (win[vi][vj] == 0) {
                    if (win[i][j] == -1) {
                        win[i][j] = 1;
                        q.push({i, j});
                    }
                } else {
                    if (deg[i][j] == 0 && win[i][j] == -1) {
                        win[i][j] = 0;
                        q.push({i, j});
                    }
                }
            }
        }
    }
    
    if (win[si][sj] == 1) {
        puts("Anton");
    } else if (win[si][sj] == 0) {
        puts("Yasha");
    } else {
        puts("draw");
    }
}
