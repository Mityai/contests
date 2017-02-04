#include <iostream>
#include <cstdio>
#include <climits>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <algorithm>
#include <set>

typedef long long ll;

using namespace std;

int main() {
    freopen("distance.in", "r", stdin);
    freopen("distance.out", "w", stdout);

    int n, m;
    scanf("%d%d", &n, &m);

    int s, f;
    scanf("%d%d", &s, &f);

    --s;
    --f;

    vector<vector<pair<int, int> > > g(n);
    vector<int> p(n);
    for (int i = 0; i < m; i++) {
        int a, b, w;
        scanf("%d%d%d", &a, &b, &w);
        
        --a;
        --b;

        g[a].push_back(make_pair(b, w));
        g[b].push_back(make_pair(a, w));
    }

    vector<int> d(n, INT_MAX);
    d[s] = 0;
    p[s] = -1;

    set<pair<int, int> > q;
    q.insert(make_pair(d[s], s));
    while (!q.empty()) {
        int v = q.begin() -> second;
        q.erase(q.begin());

        for (int i = 0; i < g[v].size(); i++) {
            int u = g[v][i].first;
            int w = g[v][i].second;

            if (d[u] > d[v] + w) {
                q.erase(make_pair(d[u], u));
                d[u] = d[v] + w;
                p[u] = v;
                q.insert(make_pair(d[u], u));
            }
        }
    }

    vector<int> path;
    for (int i = f; i != -1; i = p[i]) {
        path.push_back(i);
    }

    if (d[f] == INT_MAX) {
        printf("-1\n");
    } else {
        printf("%d\n", d[f]);
        for (int i = path.size() - 1; i >= 0; i--) {
            printf("%d ", path[i] + 1);
        }
    }
}