#include <bits/stdc++.h>
using namespace std;

void no() {
    puts("no");
    exit(0);
}

void yes() {
    puts("yes");
    exit(0);
}

const int N = 1000;

vector<int> g[N];
bool used[N];

void go(int v) {
    used[v] = true;
    for (int u : g[v]) {
        if (!used[u]) {
            go(u);
        }
    }
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    if (m == n - 1) {
        for (int i = 0; i < n - 1; ++i) {
            int a, b;
            scanf("%d%d", &a, &b);
            --a, --b;
            g[a].push_back(b);
            g[b].push_back(a);
        }
        go(0);
        bool ok = true;
        for (int i = 0; i < n; ++i) {
            ok &= used[i];
        }
        if (ok) yes();
        else no();
    } else {
        no();
    }
}
