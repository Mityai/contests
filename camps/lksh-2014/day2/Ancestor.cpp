#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cmath>

typedef long long ll;

using namespace std;

int timer;
vector<char> mark;
vector<int> tin, tout;
vector<vector<int> > g;

void dfs(int v) {
    mark[v] = true;
    tin[v] = timer++;

    for (int i = 0; i < g[v].size(); i++) {
        int u = g[v][i];
        if (!mark[u]) {
            dfs(u);
        }
    }

    tout[v] = timer++;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    scanf("%d", &n);

    tin.resize(n + 1);
    tout.resize(n + 1);
    mark.resize(n + 1, false);
    g.resize(n + 1);
    
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);

        g[x].push_back(i + 1);
    }

    timer = 0;
    dfs(0);

    int m;
    scanf("%d", &m);

    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);

        if (tin[a] < tin[b] && tout[a] > tout[b]) {
            printf("1\n");
        } else {
            printf("0\n");
        }
    }
}