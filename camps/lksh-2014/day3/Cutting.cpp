#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>

typedef long long ll;

using namespace std;

struct Req {
    string s;
    int a, b;
};

vector<int> par, ranks;

int root(int v) {
    if (v == par[v]) {
        return v;
    }

    return root(par[v]);
}

void unite(int v, int u) {
    v = root(v);
    u = root(u);

    if (ranks[v] > ranks[u]) {
        swap(v, u);
    }

    par[v] = u;

    if (ranks[v] == ranks[u]) {
        ++ranks[u];
    }
}

int main() {
    freopen("cutting.in", "r", stdin);
    freopen("cutting.out", "w", stdout);

    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);

    par.resize(n);
    ranks.resize(n);

    for (int i = 0; i < n; i++) {
        par[i] = i;
    }

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        --u;
        --v;
    }

    vector<Req> R(k);
    for (int i = 0; i < k; i++) {
        cin >> R[i].s;
        scanf("%d%d", &R[i].a, &R[i].b);
        
        --R[i].a;
        --R[i].b;
    }

    vector<string> ans;
    for (int i = k - 1; i >= 0; i--) {
        string s = R[i].s;
        int a = R[i].a, b = R[i].b;

        if (s == "ask") {
            if (root(a) == root(b)) {
                ans.push_back("YES");
            } else {
                ans.push_back("NO");
            }
        } else if (s == "cut") {
            unite(a, b);
        }
    }

    for (int i = ans.size() - 1; i >= 0; i--) {
        cout << ans[i] << endl;
    }
}