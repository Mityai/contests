#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

const int N = 1e5;
const int INF = 1234567890;
const int K = 300;
const int L = 21;

int n, m;
vector<int> g[N];
vector<int> red;
int d[N];
int up[N][L], depth[N], en[N], ex[N];
int T = 0;

void dfs(int v, int p) {
    en[v] = T++;
    depth[v] = depth[p] + 1;
    up[v][0] = p;
    for (int i = 1; i < L; i++) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    for (int u : g[v]) {
        if (u != p) {
            dfs(u, v);
        }
    }
    ex[v] = T++;
}

bool isAnc(int a, int b) {
    return en[a] <= en[b] && ex[b] <= ex[a];
}

int getLca(int v, int u) {
    for (int i = L - 1; i >= 0; i--) {
        if (!isAnc(up[v][i], u)) {
            v = up[v][i];
        }
    }
    return isAnc(v, u) ? v : up[v][0];
}

int dist(int v, int u) {
    int lca = getLca(v, u);
    return depth[v] + depth[u] - 2 * depth[lca];
}

void bfs() {
    fill(d, d + n, INF);
    queue<int> q;
    for (int v : red) {
        q.push(v);
        d[v] = 0;
    }

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int u : g[v]) {
            if (d[u] == INF) {
                d[u] = d[v] + 1;
                q.push(u);
            }
        }
    }
}

int main() {
#if __APPLE__
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#else
    //freopen(".in", "r", stdin);
    //freopen(".out", "w", stdout);
#endif

    scanf("%d%d", &n, &m);

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        --a, --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(0, 0);
    red.push_back(0);

    vector<int> toadd;
    for (int i = 0; i < m; i++) {
        if (i % K == 0) {
            for (int v : toadd) {
                red.push_back(v);
            }
            toadd.clear();
            bfs();
        }

        int t, v;
        scanf("%d%d", &t, &v);

        --v;
        if (t == 1) {
            toadd.push_back(v);
        } else {
            int res = d[v];
            for (int u : toadd) {
                res = min(res, dist(u, v));
            }
            printf("%d\n", res);
        }
    }
}
