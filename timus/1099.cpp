#include <bits/stdc++.h>
using namespace std;

const int N = 222;

vector<int> g[N];
vector<int> match;
vector<char> used;

bool dfs(int v) {
    if (used[v]) {
        return false;
    }
    used[v] = true;
    for (int u : g[v]) {
        if (match[u] == -1 || dfs(match[u])) {
            match[u] = v;
            match[v] = u;
            return true;
        }
    }
    return false;
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        --a, --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    match.resize(n, -1);
    for (int i = 0; i < n; ++i) {
        if (match[i] == -1) {
            used.assign(n, false);
            dfs(i);
        }
    }
    
    vector<pair<int, int>> ans;
    for (int i = 0; i < n; ++i) {
        if (i < match[i]) {
            ans.push_back({i, match[i]});
        }
    }

    printf("%d\n", int(ans.size()));
    for (int i = 0; i < ans.size(); ++i) {
        printf("%d %d\n", ans[i].first + 1, ans[i].second + 1);
    }
}
