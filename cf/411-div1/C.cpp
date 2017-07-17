#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

const int N = 3e5;

int n, m;
int cnt;
int col[N];
vector<int> s[N], g[N];

void go(int v, int p = -1) {
    set<int> used;
    for (int x : s[v]) {
        if (col[x] != -1) {
            used.insert(col[x]);
        }
    }

    int curcol = 0;
    for (int x : s[v]) {
        if (col[x] == -1) {
            while (used.find(curcol) != used.end()) {
                ++curcol;
            }
            col[x] = curcol++;
        }
    }

    for (int u : g[v]) {
        if (u != p) {
            go(u, v);
        }
    }
}

int main() {
#if __APPLE__
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif

    scanf("%d%d", &n, &m);

    for (int i = 0; i < n; ++i) {
        int si;
        scanf("%d", &si);

        cnt = max(cnt, si);
        for (int j = 0; j < si; ++j) {
            int x;
            scanf("%d", &x);
            --x;
            s[i].push_back(x);
        }
    }

    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        --a, --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    memset(col, -1, sizeof(col[0]) * m);
    go(0);

    cnt = max(cnt, 1);
    printf("%d\n", cnt);
    for (int i = 0; i < m; ++i) {
        if (col[i] == -1) {
            col[i] = 0;
        }
        printf("%d ", col[i] + 1);
    }
    puts("");
}
