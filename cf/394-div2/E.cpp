#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

const int N = 30;

const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, 1, 0, -1};

vector<int> g[N];
ll x[N], y[N];

const ll BOUND = 1e18;

void go(int v, int p, ll posx, ll posy, int dir, ll bnd) {
    x[v] = posx;
    y[v] = posy;
    int k = 0;
    for (int u : g[v]) {
        if (u == p) continue;
        if (k == (dir + 2) % 4) {
            ++k;
        }
        ll bnd2 = bnd / 2;
        go(u, v, posx + dx[k] * bnd2, posy + dy[k] * bnd2, k, bnd2);
        ++k;
    }
}

int main() {
#if __APPLE__
    freopen("E.in", "r", stdin);
    freopen("E.out", "w", stdout);
#endif

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        --a, --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    for (int i = 0; i < n; ++i) {
        if (g[i].size() > 4) {
            puts("NO");
            return 0;
        }
    }

    go(0, -1, 0, 0, -1123, BOUND);

    printf("YES\n");
    for (int i = 0; i < n; ++i) {
        printf("%lld %lld\n", x[i], y[i]);
    }
}
