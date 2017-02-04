#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

const int INF = 1234567890;
const int N = int(5e4);
const int K = 17;
const int s = 0;

int father[N];
int up[K][N], minCostUp[K][N];
int tin[N], tout[N];
int costToFather[N];

vector< pair<int, int> > g[N];

int n;

void calculate() {
    for (int v = 0; v < n; v++) {
        up[0][v] = father[v];
        minCostUp[0][v] = costToFather[v];
    }

    for (int k = 1; k < K; k++) {
        for (int v = 0; v < n; v++) {
            up[k][v] = up[k - 1][up[k - 1][v]];
            minCostUp[k][v] = min(minCostUp[k - 1][v], minCostUp[k - 1][up[k - 1][v]]);
        }
    }
}

bool isAncestor(int v, int u) {
    return tin[v] <= tin[u] && tout[u] <= tout[v];
}

int getAncestor(int v, int u) {
    for (int k = K - 1; k >= 0; k--) {
        if (!isAncestor(up[k][v], u)) {
            v = up[k][v];
        }
    }
    return isAncestor(v, u) ? v : father[v];
}

int getMinToAnc(int v, int anc) {
    int ret = INF;
    for (int k = K - 1; k >= 0; k--) {
        if (!isAncestor(up[k][v], anc)) {
            ret = min(ret, minCostUp[k][v]);
            v = up[k][v];
        }
    }
    return v == anc ? ret : min(ret, costToFather[v]);
}

int T = 0;
void dfs(int v, int p, int cost) {
    father[v] = p;
    costToFather[v] = cost;
    tin[v] = T++;
    for (auto to : g[v]) {
        int u = to.fi;
        int w = to.se;
        dfs(u, v, w);
    }
    tout[v] = T++;
}

int main() {
#if __APPLE__
    freopen("input.txt", "r", stdin);
#else
    freopen("minonpath.in", "r", stdin);
    freopen("minonpath.out", "w", stdout);
#endif

    scanf("%d", &n);

    for (int i = 1; i <= n - 1; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        g[x - 1].push_back({i, y});
    }

    dfs(s, s, 0);
    calculate();

    int q;
    scanf("%d", &q);

    for (int i = 0; i < q; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        --x, --y;

        int anc = getAncestor(x, y);
        int minOnPath = min(getMinToAnc(x, anc), getMinToAnc(y, anc));
        printf("%d\n", minOnPath);
    }
}
