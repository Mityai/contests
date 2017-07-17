#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

const int N = 1e5;
const int INF = 1e9;

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

vector<int> g[N];
vector<char> used;
vector<int> ver;
int need;

void go(int v) {
    ver.push_back(v);
    --need;
    used[v] = true;
    if (need == 0) return;
    for (int u : g[v]) {
        if (need == 0) return;
        if (!used[u]) {
            go(u);
        }
    }
}

void solve() {
    int n, k;
    scanf("%d%d", &n, &k);

    map<pair<int, int>, int> to;
    vector<pair<int, int>> from(n);
    int minx = INF;
    vector<pair<int, int>> ans;
    for (int i = 0; i < n; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        ans.push_back({x, y});
        to[{x, y}] = i;
        from[i] = {x, y};
        minx = min(minx, x);
    }

    for (int i = 0; i < n; ++i) {
        g[i].clear();
    }
    int st;
    for (auto& v : to) {
        int x = v.first.first;
        int y = v.first.second;
        int id = v.second;
        if (x == minx) st = id;
        for (int i = 0; i < 4; ++i) {
            int newx = x + dx[i];
            int newy = y + dy[i];
            auto it = to.find({newx, newy});
            if (it != to.end()) {
                g[id].push_back(it->second);
            }
        }
    }

    need = k - n;
    ver.clear();
    used.assign(n, false);
    go(st);

    for (int v : ver) {
        int x = - from[v].first + 2 * minx - 1;
        int y = from[v].second;
        ans.push_back({x, y});
    }

    printf("L %d\n", minx);
    for (auto& v : ans) {
        printf("%d %d\n", v.first, v.second);
    }
}

int main() {
#if __APPLE__
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif

    int t;
    scanf("%d", &t);

    for (int i = 0; i < t; ++i) {
        solve();
    }
}
