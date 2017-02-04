#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;
const int K = 18;

vector<int> g[N];
int up[N][K], en[N], ex[N], depth[N];
int T = 0;

void dfs(int v, int p) {
    en[v] = T++;
    
    depth[v] = depth[p] + 1;

    up[v][0] = p;
    for (int i = 1; i < K; i++) {
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

int jump(int v, int k) {
    for (int i = 0; i < K; i++) {
        if ((k >> i) & 1) {
            v = up[v][i];
        }
    }
    return v;
}

int main() {
    freopen("canalization.in", "r", stdin);
    freopen("canalization.out", "w", stdout);

    int n, m;
    scanf("%d%d", &n, &m);

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        --a, --b;

        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(0, 0);

    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        --a, --b;

        if (isAnc(a, b)) {
            printf("%d\n", jump(b, depth[b] - depth[a] - 1) + 1);
        } else {
            printf("%d\n", up[a][0] + 1);
        }
    }
}
