#include <bits/stdc++.h>
using namespace std;

const int N = 2e5;

int deg[N];
bool can[3][N];
vector<int> g[N];

void go(int v, int p = -1) {
    bool root = (p == -1);
    for (int u : g[v]) {
        if (u == p) continue;
        go(u, v);
    }

    can[1][v] = false;
    can[2][v] = false;
    int d = 0;
    bool qq = false;
    for (int u : g[v]) {
        if (u == p) continue;
        if (!can[1][u] && !can[2][u]) {
            return;
        } else if (can[1][u] && !can[2][u]) {
            ++d;
        } else if (can[1][u] && can[2][u]) {
            qq = true;
        }
    }
    if (qq || d % 2 == 0) {
        can[1][v] = true;
    }
    if (qq || (d + !root) % 2 == 0) {
        can[2][v] = true;
    }
    // printf("v = %d: can[1][%d] = %d, can[2][%d] = %d\n", v, v, can[1][v], v, can[2][v]);
}

void dfs(int v, int p = -1, bool has_up = false) {
    int d = has_up;
    int qq = -1;
    for (int u : g[v]) {
        if (u == p) continue;
        if (can[1][u] && !can[2][u]) {
            ++d;
        } else if (can[1][u] && can[2][u]) {
            qq = u;
        } else if (!can[1][u] && can[2][u]) {
            dfs(u, v, true);
        }
    }

    if (d % 2 == 1) {
        dfs(qq, v, true);
    }

    for (int u : g[v]) {
        if (u == p) continue;
        if (can[1][u] && can[2][u]) {
            if (u != qq) {
                dfs(u, v, true);
            }
        }
    }
    printf("%d\n", v + 1);
    for (int u : g[v]) {
        if (u == p) continue;
        if (can[1][u] && !can[2][u]) {
            dfs(u, v, false);
        }
    }
}

int main() {
#if __APPLE__
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif

    int n;
    scanf("%d", &n);

    int root = -1;
    for (int i = 0; i < n; ++i) {
        int p;
        scanf("%d", &p);
        if (p != 0) {
            --p;
            g[i].push_back(p);
            g[p].push_back(i);
            if (++deg[i] >= 2) root = i;
            if (++deg[p] >= 2) root = p;
        }
    }

    if (n == 1) {
        puts("YES");
        puts("1");
        return 0;
    } else if (n == 2) {
        puts("NO");
        return 0;
    }

    go(root);
    if (can[1][root]) {
        puts("YES");
        dfs(root);
    } else {
        puts("NO");
    }
}
