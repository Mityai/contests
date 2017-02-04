#include <bits/stdc++.h>
#define open asdasf
#define close jlkasdf
#define fi first
#define se second
using namespace std;

typedef long long ll;

const int N = 1e5;

vector<int> g[N];
int sz[N], parent[N], used[N], col[N];
unordered_map<int, int> near[N];

ll ans = 0;

void calcsz(int v, int p) {
    sz[v] = 1;
    for (int u : g[v]) {
        if (u != p && !used[u]) {
            calcsz(u, v);
            sz[v] += sz[u];
        }
    }
}

int dfs(int v, int p, int n) {
    for (int u : g[v]) {
        if (u != p && !used[u] && sz[u] > n / 2) {
            return dfs(u, v, n);
        }
    }
    return v;
}

map<int, int> open[N], close[N];
map<int, int> allopen, allclose;

void goopen(int v, int p, int b, int balance, int st) {
    if (col[v] == 0) b = max(0, b - 1), balance++;
    else b++, balance--;

    if (b == 0) {
        open[st][balance]++;
        allopen[balance]++;
    }

    for (int u : g[v]) {
        if (u != p && !used[u]) {
            goopen(u, v, b, balance, st);
        }
    }
}

void goclose(int v, int p, int b, int balance, int st) {
    if (col[v] == 1) b = max(0, b - 1), balance++;
    else b++, balance--;

    if (b == 0) {
        close[st][balance]++;
        allclose[balance]++;
    }

    for (int u : g[v]) {
        if (u != p && !used[u]) {
            goclose(u, v, b, balance, st);
        }
    }
}

void calc(int v) {
    for (int u : g[v]) {
        if (!used[u]) {
            goopen(u, v, 0, 0, u);
            goclose(u, v, col[v] == 0, col[v] == 0 ? -1 : 1, u);
        }
    }
    for (int u : g[v]) {
        if (!used[u]) {
            for (auto x : open[u]) {
                ans += (allclose[x.fi] - close[u][x.fi]) * x.se;
            }
            if (col[v] == 1) {
                ans += open[u][1];
            } else {
                ans += close[u][0];
            }
        }
    }
    allopen.clear();
    allclose.clear();
    for (int u : g[v]) {
        if (!used[u]) {
            open[u].clear();
            close[u].clear();
        }
    }
}

void build(int v, int p = -1) {
    calcsz(v, v);
    int center = dfs(v, v, sz[v]);
    if (p == -1) parent[center] = center;
    else parent[center] = p;
    used[center] = true;

    calc(center);

    for (int u : g[center]) {
        if (!used[u]) {
            build(u, center);
        }
    }
}

int main() {
    freopen("balanced-strings.in", "r", stdin);
    freopen("balanced-strings.out", "w", stdout);

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        char c;
        scanf(" %c", &c);
        col[i] = (c == '(' ? 0 : 1);
    }

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        --a, --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    build(0);

    cout << ans << endl;
}
