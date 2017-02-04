#include <bits/stdc++.h>
#define fi first
#define se second

using namespace std;

using ll = long long;

const ll INF = 2e9;
const int N = 5e3 + 123;

vector<pair<int, int>> g[N];
vector<int> indeg;
bool used[N];

void go(int v) {
    used[v] = true;
    for (auto& to : g[v]) {
        int u = to.fi;
        ++indeg[u];
        if (!used[u]) {
            go(u);
        }
    }
}

int main() {
#if __APPLE__
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif

    int n, m, T;
    scanf("%d%d%d", &n, &m, &T);

    indeg.resize(n);
    for (int i = 0; i != m; ++i) {
        int a, b, t;
        scanf("%d%d%d", &a, &b, &t);
        --a, --b;
        g[a].push_back({b, t});
    }

    go(0);

    queue<int> q;
    q.push(0);

    vector<vector<int>> dp(n, vector<int>(n + 1, INF));
    vector<vector<short>> prev(n, vector<short>(n + 1, -1));
    dp[0][1] = 0;
    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (auto& to : g[v]) {
            int u = to.fi;
            ll t = to.se;

            for (int cnt = 1; cnt < n; cnt++) {
                if (dp[v][cnt] != INF) {
                    if (dp[v][cnt] + t <= T && dp[u][cnt + 1] > dp[v][cnt] + t) {
                        dp[u][cnt + 1] = dp[v][cnt] + t;
                        prev[u][cnt + 1] = v;
                    }
                }
            }

            --indeg[u];
            if (indeg[u] == 0) {
                q.push(u);
            }
        }
    }

    int anscnt = 0;
    for (int i = n; i >= 1; i--) {
        if (dp[n - 1][i] <= T) {
            anscnt = i;
            break;
        }
    }

    vector<int> anspath;
    anspath.reserve(n);
    for (int v = n - 1; anscnt != 0; v = prev[v][anscnt--]) {
        anspath.push_back(v);
        assert(anspath.size() <= n);
    }

    reverse(anspath.begin(), anspath.end());

    printf("%d\n", int(anspath.size()));
    for (int x : anspath) {
        printf("%d ", x + 1);
    }
    puts("");
}
