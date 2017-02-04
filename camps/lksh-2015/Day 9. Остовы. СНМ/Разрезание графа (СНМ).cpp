#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

const int N = 5e4;

int parent[N], ranks[N];

void initDSU(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        ranks[i] = 0;
    }
}

int root(int v) {
    return v == parent[v] ? v : parent[v] = root(parent[v]);
}

void join(int v, int u) {
    v = root(v);
    u = root(u);

    if (ranks[v] < ranks[u]) {
        swap(v, u);
    }

    parent[u] = v;

    if (ranks[v] == ranks[u]) {
        ranks[v]++;
    }
}

int main() {
#if __APPLE__
    freopen("input.txt", "r", stdin);
#else
    freopen("cutting.in", "r", stdin);
    freopen("cutting.out", "w", stdout);
#endif

    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);

    initDSU(n);

    for (int i = 0; i < m; i++) {
        int trash1, trash2;
        scanf("%d%d", &trash1, &trash2);
    }

    vector< pair<string, pair<int, int> > > q(k);
    for (int i = 0; i < k; i++) {
        cin >> q[i].fi;
        scanf("%d%d", &q[i].se.fi, &q[i].se.se);
        q[i].se.fi--, q[i].se.se--;
    }
    vector<string> ans;

    for (int i = k - 1; i >= 0; i--) {
        string s = q[i].fi;
        int v = q[i].se.fi;
        int u = q[i].se.se;
        if (s == "ask") {
            ans.push_back(root(v) == root(u) ? "YES" : "NO");
        } else {
            join(v, u);
        }
    }

    for (int i = (int)ans.size() - 1; i >= 0; i--) {
        printf("%s\n", ans[i].c_str());
    }
}
