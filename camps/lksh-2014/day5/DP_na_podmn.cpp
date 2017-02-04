#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cmath>

typedef long long ll;

using namespace std;

vector<vector<int> > g;
vector<char> d;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    scanf("%d", &n);

    g.resize(n);
    d.resize(1 << n, false);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            char c;
            scanf(" %c", &c);

            if (c == 'Y') {
                g[i].push_back(j);
            }
        }
    }

    d[0] = true;

    for (int mask = 0; mask < (1 << n); mask++) {
        if (d[mask]) {
            for (int v = 0; v < n; v++) {
                for (int i = 0; i < g[v].size(); i++) {
                    int u = g[v][i];
                    if (!(mask & (1 << v)) && !(mask & (1 << u))) {
                        d[mask | (1 << v) | (1 << u)] = true;
                    }
                }
            }
        }
    }

    int ans = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        int cur = 0;
        if (d[mask]) {
            for (int v = 0; v < n; v++) {
                if (mask & (1 << v)) {
                    ++cur;
                }
            }
        }
        ans = max(ans, cur);
    }

    printf("%d\n", ans);
}