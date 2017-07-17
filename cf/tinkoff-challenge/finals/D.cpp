#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

const int N = 3e5;

vector<int> g[N];
int col[N];
bool used[N];
set<int> usedall;
map<int, int> to;

void no() {
    puts("NO");
    exit(0);
}

void go(int v, int c) {
    used[v] = true;
    col[v] = c;
    usedall.insert(c);
    if (g[v].size() > 2) {
        no();
    }
    set<int> can({c - 1, c + 1});
    if (usedall.find(c - 1) != usedall.end()) {
        can.erase(c - 1);
    }
    if (usedall.find(c + 1) != usedall.end()) {
        can.erase(c + 1);
    }
    int need = 0;
    for (int u : g[v]) {
        if (used[u]) {
            if (c == col[u]) no();
            can.erase(col[u]);
        } else {
            ++need;
        }
    }
    if (can.size() < need) {
        no();
    }
    for (int u : g[v]) {
        if (!used[u]) {
            go(u, *can.begin());
            can.erase(can.begin());
        }
    }
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    vector<pair<vector<int>, int>> gn(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        --a, --b;
        gn[a].se = a;
        gn[b].se = b;
        gn[a].fi.push_back(b);
        gn[b].fi.push_back(a);
    }

    for (int i = 0; i < n; ++i) {
        gn[i].fi.push_back(i);
        sort(gn[i].fi.begin(), gn[i].fi.end());
    }

    sort(gn.begin(), gn.end());
    int k = 0;
    for (int i = 0; i < n; ++i) {
        if (i > 0 && gn[i].fi == gn[i - 1].fi) {
            to[gn[i].se] = k - 1;
        } else {
            to[gn[i].se] = k;
            ++k;
        }
    }

    for (int i = 0; i < n; ++i) {
        if (i > 0 && to[gn[i].se] == to[gn[i - 1].se]) {
            continue;
        } else {
            set<int> qv;
            int id = gn[i].se;
            auto& v = gn[i].fi;
            for (int x : v) {
                if (to[x] != to[id]) {
                    qv.insert(to[x]);
                }
            }
            g[to[id]] = vector<int>(qv.begin(), qv.end());
        }
    }

    go(0, 0);

    int minval = 1e9;
    for (int i = 0; i < k; ++i) {
        minval = min(minval, col[i]);
    }
    puts("YES");
    for (int i = 0; i < n; ++i) {
        int c = col[to[i]] - minval + 1;
        printf("%d ", c);
    }
    puts("");
}
