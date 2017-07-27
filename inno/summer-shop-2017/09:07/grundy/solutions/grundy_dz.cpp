#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;

vector<int> g[N];
int grundy[N];

int go(int v) {
    if (grundy[v] != -1) return grundy[v];
    vector<int> cur;
    for (int u : g[v]) {
        cur.push_back(go(u));
    }
    sort(cur.begin(), cur.end()); cur.erase(unique(cur.begin(), cur.end()), cur.end());
    int j;
    for (j = 0; j < cur.size(); ++j) {
        if (j != cur[j]) break;
    }
    return grundy[v] = j;
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    vector<int> out(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        --a, --b;
        g[a].push_back(b);
    }

    fill(grundy, grundy + n, -1);

    for (int i = 0; i < n; ++i) {
        if (grundy[i] == -1) {
            go(i);
        }
    }

    for (int i = 0; i < n; ++i) {
        printf("%d\n", grundy[i]);
    }
}
