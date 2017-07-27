#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;
struct edge {
    int u, num;
    edge(int a = 0, int c = 0) : u(a), num(c) {}
};
vector <int> f, c, used;
vector <vector <edge> >g;
int n, m, s, t;
int dfs(int v, int cmin) {
    if (v == t)
        return cmin;
    used[v] = 1;
    for (edge e : g[v]) {
        if (!used[e.u]) {
            int ost = c[e.num] - f[e.num];
            int delta = 0;
            if (ost > 0)
                delta = dfs(e.u, min(cmin, ost));
            f[e.num] += delta;
            f[(e.num ^ 1)] -= delta;
            if (delta != 0)
                return delta;
        }
    }
    return 0;
}
void dfs_way(int v) {
    used[v] = 1;
    cout << v + 1 << " ";
    if (v == t)
        return;
    for (edge e : g[v]) {
        if ((!used[e.u]) && f[e.num] == 1) {
            dfs_way(e.u);
            f[e.num] = 0;
            f[e.num ^ 1] = 0;
            return;
        }
    }
}
int main() {
    ios_base::sync_with_stdio(0);
    freopen("snails.in", "r", stdin);
    freopen("snails.out", "w", stdout);
    cin >> n >> m;
    cin >> s >> t;
    s--;
    t--;
    c.resize(2 * m);
    g.resize(n);
    f.resize(2 * m);
    for (int i = 0; i < m; i++) {
        int v, u, x;
        cin >> v >> u;
        v--;
        u--;
        g[v].push_back(edge(u, 2 * i));
        g[u].push_back(edge(v, ((2 * i) ^ 1)));
        c[i * 2] = 1;
        c[((i * 2) ^ 1)] = 0;
        f[i * 2] = 0;
        f[((i * 2) ^ 1)] = 0;
    }
    used.resize(n);
    int ans = 0;
    while (ans < 2) {
        used.assign(n, 0);
        int delta = dfs(s, 10);
        if (delta == 0)
            break;
        ans += delta;
    }
    if (ans < 2) {
        cout << "NO";
        return 0;
    }
    cout << "YES" << "\n";
    used.assign(n, 0);
    dfs_way(s);
    cout << "\n";
    used.assign(n, 0);
    dfs_way(s);
    return 0;
}
