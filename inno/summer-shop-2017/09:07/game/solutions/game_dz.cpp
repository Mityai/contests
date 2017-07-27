#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;

int win[N];
vector<int> g[N];

bool go(int v) {
    if (win[v] != -1) return win[v];
    win[v] = 0;
    for (int u : g[v]) {
        if (!go(u)) {
            win[v] = 1;
            break;
        }
    }
    return win[v];
}

int main() {
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);

    int n, m, s;
    scanf("%d%d%d", &n, &m, &s);
    --s;

    for (int i = 0; i < m; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        --a, --b;
        g[a].push_back(b);
    }

    fill(win, win + n, -1);
    if (go(s)) {
        puts("First player wins");
    } else {
        puts("Second player wins");
    }
}
