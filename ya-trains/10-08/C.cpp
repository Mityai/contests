#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

const int N = 234567;

vector<int> g[N];
int sz;
bool used[N];
int color[N];

void dfs(int v, map<int, int>& cnt) {
    ++sz;
    used[v] = true;
    ++cnt[color[v]];
    for (int to : g[v]) {
        if (!used[to]) dfs(to, cnt);
    }
}

int main() {
    ios::sync_with_stdio(0);
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 0; i < n; ++i) {
        cin >> color[i];
    }
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        --x;
        --y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    int res = 0;
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            map<int, int> cnt;
            sz = 0;
            dfs(i, cnt);
            int mx = 0;
            for (auto w : cnt) {
                mx = max(mx, w.second);
            }
            res += sz - mx;
        }
    }
    cout << res;
    return 0;
}
