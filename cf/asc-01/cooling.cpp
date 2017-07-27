#include <bits/stdc++.h>
using namespace std;

const int INF = 1234567890;

const int N = 200 + 2;
const int M = 6 * (N * (N - 1) / 2);

const int s = N - 1;
const int t = N - 2;

vector<int> E[N];
int flow[M], cap[M], to[M];
int e = 0;

void add_edge(int v, int u, int c) {
    to[e] = u;
    to[e ^ 1] = v;

    cap[e] = c;
    cap[e ^ 1] = 0;

    E[v].push_back(e);
    E[u].push_back(e ^ 1);

    e += 2;
}

int dist[N], first[N];

bool bfs(int up = 1) {
    fill(dist, dist + N, INF);
    queue<int> q;
    q.push(s);
    dist[s] = 0;

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int e : E[v]) {
            int u = to[e];
            if (dist[u] == INF && cap[e] - flow[e] >= up) {
                dist[u] = dist[v] + 1;
                q.push(u);
            }
        }
    }
    return dist[t] != INF;
}

int dfs(int v, int cur_flow, int up = 1) {
    if (v == t || cur_flow == 0) {
        return cur_flow;
    }
    for (int& i = first[v]; i < E[v].size(); ++i) {
        int e = E[v][i];
        int u = to[e];
        if (dist[u] == dist[v] + 1 && cap[e] - flow[e] >= up) {
            int a = dfs(u, min(cur_flow, cap[e] - flow[e]), up);
            if (a > 0) {
                flow[e] += a;
                flow[e ^ 1] -= a;
                return a;
            }
        }
    }
    return 0;
}

void doMaxFlow() {
    for (int up = 1 << 17; up >= 1; up >>= 1) {
        while (bfs(up)){
            memset(first, 0, sizeof first);
            while (dfs(s, INF, up) > 0);
        }
    }
}

bool isFull() {
    for (int e : E[s]) {
        if (flow[e] < cap[e]) {
            return false;
        }
    }
    return true;
}

int main() {
    freopen("cooling.in", "r", stdin);
    freopen("cooling.out", "w", stdout);

    int n, m;
    scanf("%d%d", &n, &m);

    vector<int> num(m), add(m);
    for (int i = 0; i < m; ++i) {
        int a, b, l, r;
        scanf("%d%d%d%d", &a, &b, &l, &r);
        --a, --b;
        num[i] = e;
        add[i] = l;
        add_edge(a, b, r - l);
        add_edge(s, b, l);
        add_edge(a, t, l);
    }


    doMaxFlow();
    if (!isFull()) {
        puts("NO");
    } else {
        puts("YES");
        for (int i = 0; i < m; ++i) {
            printf("%d\n", flow[num[i]] + add[i]);
        }
    }
}
