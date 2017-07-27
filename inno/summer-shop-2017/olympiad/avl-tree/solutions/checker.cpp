#include <bits/stdc++.h>
using namespace std;

const int N = 100;

vector<int> g[N];
int height[N];

void go(int v) {
    height[v] = 1;
    for (int u : g[v]) {
        go(u);
        height[v] = max(height[v], height[u] + 1);
    }
}

int main() {
    freopen("in.txt", "r", stdin);

    int n = 93, h = 9;
    for (int i = 1; i <= n - 1; ++i) {
        int p;
        scanf("%d", &p);
        g[p - 1].push_back(i);
    }
    go(0);

    if (height[0] != h) {
        puts("FAIL height");
    }

    for (int i = 0; i < n; ++i) {
        int l = 0, r = 0;
        if (g[i].size() >= 1) {
            l = height[g[i][0]];
        }
        if (g[i].size() == 2) {
            r = height[g[i][1]];
        }
        assert(g[i].size() <= 2);
        if (abs(l - r) > 1) {
            puts("FAIL abs <= 1");
        }
    }
}
