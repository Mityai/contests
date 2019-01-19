#include <bits/stdc++.h>
using namespace std;

bool find_path(int v, int en, const vector<vector<int>>& g, vector<int>& path, int p = -1) {
    path.push_back(v);
    if (v == en) return true;
    for (int u : g[v]) {
        if (u != p) {
            if (find_path(u, en, g, path, v)) {
                return true;
            }
        }
    }
    path.pop_back();
    return false;
}

int get_cnt(int v, const vector<vector<int>>& g, const vector<char>& mark, int p = -1) {
    int cnt = 1;
    for (int u : g[v]) {
        if (u != p && !mark[u]) {
            cnt += get_cnt(u, g, mark, v);
        }
    }
    return cnt;
}

int main() {
    int n;
    int a, b;
    scanf("%d%d%d", &n, &a, &b);
    --a, --b;
    
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        --a, --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    vector<int> path;
    find_path(a, b, g, path);
    
    vector<char> mark(n);
    for (int v : path) mark[v] = true;

    int cnt1 = get_cnt(a, g, mark);
    int cnt2 = get_cnt(b, g, mark);

    long long all = n * 1ll * (n - 1);
    long long bad = cnt1 * 1ll * cnt2;
    printf("%lld\n", all - bad);
}
