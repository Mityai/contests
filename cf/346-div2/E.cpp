#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

const int N = 1e5;

vector<int> g[N];
int mark[N];
int cnt[N];
int ed[N];

void dfs(int v, int c) {
    mark[v] = c;
    cnt[c]++;
    for (int u : g[v]) {
        if (mark[u] == -1) {
            dfs(u, c);
        }
    }
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    vector< pair<int, int> > e(m);
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &e[i].fi, &e[i].se);
        --e[i].fi, --e[i].se;
        g[e[i].fi].push_back(e[i].se);
        g[e[i].se].push_back(e[i].fi);
    }

    memset(mark, -1, sizeof mark);

    int c = 0;
    for (int i = 0; i < n; i++) {
        if (mark[i] == -1) {
            dfs(i, c++);
        }
    }

    for (int i = 0; i < m; i++) {
        ed[mark[e[i].fi]]++;
    }

    int ans = 0;
    for (int i = 0; i < c; i++) {
        if (ed[i] == cnt[i] - 1) {
            ans++;
        }
    }

    printf("%d\n", ans);
}
