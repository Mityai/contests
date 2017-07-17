#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

const int N = 5e4;

#if __APPLE__
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define eprintf(...)
#endif

int n, k;
int a[N], dp[N], bot[N], par[N];
vector<pair<int, int>> g[N];
bool used[N];

int best_value = -1, lca, st, en;

void go(int v, int p) {
    par[v] = p;
    used[v] = true;
    vector<pair<int, int>> best;
    for (auto& to : g[v]) {
        int u = to.first;
        int w = to.second;
        if (u == p) continue;
        go(u, v);
        best.push_back({dp[u] + w, u});
    }
    while (best.size() < 2) {
        best.push_back({0, v});
    }
    bot[v] = v;
    sort(best.rbegin(), best.rend());
    if (best_value < a[v] + best[0].first + best[1].first) {
        best_value = a[v] + best[0].first + best[1].first;
        st = bot[best[0].second];
        en = bot[best[1].second];
        lca = v;
    }
    bot[v] = bot[best[0].second];
    dp[v] = a[v] + best[0].first;
}

int main() {
    scanf("%d%d", &n, &k);

    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }

    for (int i = 0; i < k; ++i) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        g[u - 1].push_back({v - 1, c});
        g[v - 1].push_back({u - 1, c});
    }

    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            go(i, i);
        }
    }

    printf("%d\n", best_value);
    vector<int> path1, path2;
    for (int v = st; v != lca; v = par[v]) {
        path1.push_back(v);
    }
    for (int v = en; v != lca; v = par[v]) {
        path2.push_back(v);
    }
    reverse(path1.begin(), path1.end());
    printf("%d\n", int(path1.size() + 1 + path2.size()));
    for (int x : path2) {
        printf("%d ", x + 1);
    }
    printf("%d ", lca + 1);
    for (int x : path1) {
        printf("%d ", x + 1);
    }
    puts("");
}
