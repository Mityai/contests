#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

const int N = 2e5;

vector<int> g[N];
int maxdeg;
int col[N];

void go(int v, int p, int c) {
    col[v] = c;
    int curc = 0;
    for (int u : g[v]) {
        if (u != p) {
            while (curc == col[v] || curc == col[p]) {
                ++curc;
            }
            go(u, v, curc);
            ++curc;
        }
    }
}

int main() {
#if __APPLE__
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
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
        maxdeg = max(maxdeg, (int)g[i].size() + 1);
    }

    go(0, 0, 0);

    printf("%d\n", maxdeg);
    for (int i = 0; i < n; ++i) {
        printf("%d ", col[i] + 1);
    }
}
