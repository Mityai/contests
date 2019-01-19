#include <bits/stdc++.h>
using namespace std;

const int N = 3e5;

char mark[N];
char col[N + 1];

vector<int> g[N];
vector<vector<int>> cnt(26, vector<int>(N));

bool dfs(int v) {
    mark[v] = 1;
    cnt[col[v] - 'a'][v] = 1;
    for (int u : g[v]) {
        if (mark[u] == 1) {
            return true;
        } else if (mark[u] == 0) {
            if (dfs(u)) return true;
        }
        for (int c = 0; c < 26; ++c) {
            cnt[c][v] = max(cnt[c][v], cnt[c][u] + ((col[v] - 'a') == c));
        }
    }
    mark[v] = 2;
    return false;
}

void inf() {
    puts("-1");
    exit(0);
}

int main() {
#if __APPLE__
    freopen("D.in", "r", stdin);
    freopen("D.out", "w", stdout);
#endif

    int n, m;
    scanf("%d%d", &n, &m);

    scanf(" %s", col);

    for (int i = 0; i < m; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        --a, --b;
        g[a].push_back(b);
    }

    for (int i = 0; i < n; ++i) {
        if (mark[i] == 0) {
            if (dfs(i)) {
                inf();
            }
        }
    }

    int ans = 0;
    for (int c = 0; c < 26; ++c) {
        for (int i = 0; i < n; ++i) {
            ans = max(ans, cnt[c][i]);
        }
    }
    printf("%d\n", ans);
}
