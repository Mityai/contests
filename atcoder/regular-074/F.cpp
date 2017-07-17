#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

const int INF = 1e9;
const int M = 100;
const int N = 2 * 2 * M * M;

vector<int> E[N];
int flow[N], cap[N], to[N];
bool used[N];

const int s = 0, t = N - 1;

int e = 0;

void addEdge(int v, int u, int c) {
    E[v].push_back(e);
    E[u].push_back(e ^ 1);

    cap[e] = c;
    cap[e ^ 1] = 0;

    to[e] = u;
    to[e ^ 1] = v;

    e += 2;
}

int push(int v, int cur_flow) {
    if (v == t || cur_flow == 0) {
        return cur_flow;
    }

    used[v] = true;
    for (int edge : E[v]) {
        if (!used[to[edge]]) {
            int a = push(to[edge], min(cur_flow, cap[edge] - flow[edge]));
            if (a > 0) {
                flow[edge] += a;
                flow[edge ^ 1] -= a;
                return a;
            }
        }
    }
    return 0;
}

int main() {
#if __APPLE__
    //freopen("F.in", "r", stdin);
    //freopen("F.out", "w", stdout);
#endif

    ios_base::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    vector<string> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];

        for (int j = 0; j < m; ++j) {
            if (a[i][j] == 'o') {
                addEdge(i + 1, n + j + 1, 1);
                addEdge(n + j + 1, i + 1, 1);
            }
            if (a[i][j] == 'S') {
                addEdge(s, i + 1, INF);
                addEdge(s, n + j + 1, INF);
            }
            if (a[i][j] == 'T') {
                addEdge(i + 1, t, INF);
                addEdge(n + j + 1, t, INF);
            }
        }
    }

    int ans = 0;
    int curflow;
    while ((curflow = push(s, INF)) > 0) {
        ans += curflow;
        memset(used, 0, sizeof used);
    }

    if (ans >= INF) ans = -1;
    printf("%d\n", ans);
}
