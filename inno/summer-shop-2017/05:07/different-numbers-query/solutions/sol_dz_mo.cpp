#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;
const int K = 1000;

vector<pair<int, int>> g[N];

int flatten[2 * N], first[N], last[N];

void dfs(int v, int p) {
    static int timer = 0;
    flatten[timer] = v;
    first[v] = timer++;
    for (const auto& to : g[v]) {
        int u = to.first;
        int w = to.second;
        if (u != p) {
            if (first[v] == -1) first[v] = timer;
            go(u, v);
        }
    }
}

bool cmp(const pair<int, int>& a, const pair<int, int>& b) {
    return a.first / K < b.first / K ||
           (a.first / K == b.first / K && a.second < b.second);
}

int main() {
    int n, q;
    scanf("%d%d", &n, &q);

    for (int i = 0; i < n - 1; ++i) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        --u, --v;

        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    fill(first, first + n, -1);
    dfs(0, 0);

    vector<pair<int, int>> queries(q);
    for (int i = 0; i < q; ++i) {
        scanf("%d%d", &queries[i].first, &queries[i].second);
    }

    sort(queries.begin(), queries.end(), cmp);
    for (int i = 0; i < n; ++i) {

    }
}
