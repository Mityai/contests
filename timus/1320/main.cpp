#include <bits/stdc++.h>
using namespace std;

const int N = 1e3;

vector<int> g[N];
int col[N];

void paint(int v, int c) {
    col[v] = c;
    for (int u : g[v]) {
        if (col[u] == 0) {
            paint(u, c);
        }
    }
}

int main() {
    int a, b;
    vector<pair<int, int>> edges;
    while (scanf("%d%d", &a, &b) == 2) {
        --a, --b;
        edges.push_back({a, b});
        g[a].push_back(b);
        g[b].push_back(a);
    }

    int c = 1;
    for (int i = 0; i < N; ++i) {
        if (col[i] == 0) {
            paint(i, c++);
        }
    }

    vector<int> cnt(c);
    for (auto& v : edges) {
        ++cnt[col[v.first]];
    }

    for (int i = 0; i < c; ++i) {
        if (cnt[i] & 1) {
            puts("0");
            return 0;
        }
    }
    puts("1");
}
