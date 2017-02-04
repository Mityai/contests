#include <bits/stdc++.h>
#define is_same fsadjlkfjasdkl
using namespace std;

using ll = long long;

const int N = 1e5;

int n;
vector<int> g[N];
int col[N];
int cnt_col[N + 1];
int sz[N];
bool is_same[N];

void dfs(int v, int p) {
    is_same[v] = true;
    sz[v] = 1;
    for (int u : g[v]) {
        if (u == p) continue;
        dfs(u, v);
        sz[v] += sz[u];
        if (!is_same[u] || col[u] != col[v]) {
            is_same[v] = false;
        }
    }

    bool ok = true;
    for (int u : g[v]) {
        if (u == p) continue;
        if (!is_same[u]) {
             ok = false;
        }
        cnt_col[col[u]] -= sz[u];
    }
    --cnt_col[col[v]];

    int left = n - sz[v];
    if (p != -1 && cnt_col[col[p]] < left) ok = false;
    if (ok) {
        printf("YES\n%d\n", v + 1);
        exit(0);
    }

    ++cnt_col[col[v]];
    for (int u : g[v]) {
        if (u == p) continue;
        cnt_col[col[u]] += sz[u];
    }
}

int main() {
#if __APPLE__
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
#endif

    scanf("%d", &n);

    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        --a, --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    for (int i = 0; i < n; ++i) {
        scanf("%d", &col[i]);
        ++cnt_col[col[i]];
    }

    dfs(0, -1);
    puts("NO");
}
