#include <bits/stdc++.h>
#define left sadfasdf
#define fi first
#define se second
using namespace std;

using ll = long long;

const int N = 2e5;

vector<int> g[N];

bool used[N];
int tour[2 * N];
int cnt;

void go(int v) {
    used[v] = true;
    tour[cnt++] = v;
    for (int u : g[v]) {
        if (!used[u]) {
            go(u);
            tour[cnt++] = v;
        }
    }
}

int main() {
#if __APPLE__
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif

    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);

    for (int i = 0; i < m; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        --a, --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    go(0);

    int maxlen = (2 * n + k - 1) / k;
    for (int i = 0; i < k; ++i) {
        int l = min(i * maxlen, cnt - 1);
        int r = min((i + 1) * maxlen, cnt);
        printf("%d ", r - l);
        for (int j = l; j < r; ++j) {
            printf("%d ", tour[j] + 1);
        }
        puts("");
    }
}
