#include <bits/stdc++.h>
using namespace std;

const int N = 1e6;

int depth[N];

vector<int> g[N];

void go(int v, int p, int d) {
    depth[v] = d;
    for (int u : g[v]) {
        if (u != p) {
            go(u, v, d + 1);
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);

    int one[n];
    for (int i = 0; i < n; ++i) {
        scanf("%d", &one[i]);
    }

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    for (int i = 0; i < n; ++i) {
        if (one[i]) {
            go(i, -1, 0);
            break;
        }
    }

    int further = 0;
    for (int i = 0; i < n; ++i) {
        if (depth[i] > depth[further] && one[i]) {
            further = i;
        }
    }

    memset(depth, 0, sizeof depth);
    if (one[further]) {
        go(further, -1, 0);
    }

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        if (one[i]) {
            ans = max(ans, depth[i]);
        }
    }

    cout << (ans + 1) / 2 << endl;
}
