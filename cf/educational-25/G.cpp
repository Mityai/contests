#include <bits/stdc++.h>
using namespace std;

inline int readInt() {
    char c = getchar();
    while (c <= 32) c = getchar();
    int ret = 0;
    while ('0' <= c && c <= '9') ret = ret * 10 + c - '0', c = getchar();
    return ret;
}

const int N = 1e6;

vector<int> g[N];
int min_to[N], par[N];
int min_to_black = N;
bool used[N];

void dfs(int v, int p, int cur_min) {
    par[v] = p;
    min_to[v] = cur_min;
    for (int u : g[v]) {
        if (u != p) {
            dfs(u, v, min(cur_min, u));
        }
    }
}

void update(int v) {
    while (!used[v]) {
        used[v] = true;
        min_to_black = min(min_to_black, v);
        if (v == par[v]) break;
        v = par[v];
    }
}

int main() {
    int n = readInt();
    int q = readInt();

    for (int i = 0; i < n - 1; ++i) {
        int a = readInt() - 1;
        int b = readInt() - 1;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    for (int i = 0, last = 0; i < q; ++i) {
        int t = readInt();
        int z = readInt();
        int x = (z + last) % n;

        if (i == 0) {
            dfs(x, x, x);
        }
        if (t == 1) {
            update(x);
        } else {
            last = min(min_to_black, min_to[x]) + 1;
            printf("%d\n", last);
        }
    }
}
