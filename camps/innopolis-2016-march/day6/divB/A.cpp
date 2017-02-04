#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;

vector<int> g[N];
bool used[N];
vector<int> ans;

void go(int v, bool f) {
    used[v] = true;
    if (f) ans.push_back(v);
    for (int u : g[v]) {
        if (!used[u]) {
            go(u, 1 - f);
        }
    }
}

int main() {
    freopen("tournament.in", "r", stdin);
    freopen("tournament.out", "w", stdout);

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        --a, --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    int k;
    scanf("%d", &k);

    for (int i = 0; i < n; i++) {
        if (!used[i]) go(i, true);
    }

    if (ans.size() < k) puts("0");
    else {
        for (int i = 0; i < k; i++) {
            printf("%d ", ans[i] + 1);
        }
        puts("");
    }
}
