#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

const int N = 1e4;

int n;
int p[N];
int f[N];

int go(int v) {
    if (f[v] != -1) return f[v];
    if (p[p[v]] == v && p[v] >= v) return f[v] = v;
    return f[v] = go(p[v]);
}

int main() {
    scanf("%d", &n);
    memset(f, -1, n * sizeof(f[0]));
    for (size_t i = 0; i != n; ++i) {
        scanf("%d", &p[i]);
        --p[i];
    }

    set<int> trees;
    for (int v = 0; v < n; ++v) {
        trees.insert(go(v));
    }

    printf("%d\n", int(trees.size()));
}
