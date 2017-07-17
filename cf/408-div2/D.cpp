#include <algorithm>
#include <vector>
#include <cstdio>
#include <set>
#include <queue>
using namespace std;

const int N = 3e5;
const int INF = 1e9;

vector<pair<int, int>> g[N];
int dist[N];
int p[N];
set<int> ans;
int n, k, d;

void go(int v, int par = -1) {
    for (auto& to : g[v]) {
        int u = to.first;
        int id = to.second;
        if (p[v] != p[u]) {
            ans.insert(id);
        }
        if (u != par) {
            go(u, v);
        }
    }
}

int main() {
    scanf("%d%d%d", &n, &k, &d);
    
    vector<char> police(n, false);
    for (int i = 0; i < k; ++i) {
        int pol;
        scanf("%d", &pol);
        police[pol - 1] = true;
    }

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        --u, --v;
        g[u].push_back({v, i});
        g[v].push_back({u, i});
    }

    fill(dist, dist + n, INF);
    queue<int> q;
    for (int i = 0; i < n; ++i) {
        if (police[i]) {
            dist[i] = 0;
            p[i] = i;
            q.push(i);
        }
    }
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto& to : g[v]) {
            int u = to.first;
            if (dist[u] > dist[v] + 1) {
                dist[u] = dist[v] + 1;
                p[u] = p[v];
                q.push(u);
            }
        }
    }

    go(0);

    printf("%d\n", int(ans.size()));
    for (int edge : ans) {
        printf("%d ", edge + 1);
    }
}
