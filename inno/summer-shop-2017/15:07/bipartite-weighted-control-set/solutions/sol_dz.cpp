#include <bits/stdc++.h>
using namespace std;

#if __APPLE__
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define eprintf(...)
#endif

const int INF = 1e9;
const int INF_FLOW = 1e9;

const int N = 1e4 * 2 + 2;
const int M = 1e4 + 1e4 + 1e5;

vector<int> edge[N];

int dist[N];
int flow[M + M], cap[M + M], to[M + M];
int first[N];

int e = 0;

const int s = N - 1;
const int t = N - 2;

void addEdge(int u, int v, int c, bool undir = false) {
    to[e] = v;
    to[e ^ 1] = u;

    cap[e] = c;
    cap[e ^ 1] = undir * c;

    edge[u].push_back(e);
    edge[v].push_back(e ^ 1);

    e += 2;
}

bool bfs(int up_flow) {
    memset(dist, 127, sizeof dist);
    const int CUR_INF = dist[0];

    dist[s] = 0;
    queue<int> q({s});
    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (int ed : edge[v]) {
            int u = to[ed];
            if (dist[u] == CUR_INF && cap[ed] - flow[ed] >= up_flow) {
                dist[u] = dist[v] + 1;
                q.push(u);
            }
        }
    }
    return dist[t] != CUR_INF;
}

int push(int v, int cur_flow, int up_flow) {
    if (v == t || cur_flow == 0) {
        return cur_flow;
    }

    for (int& i = first[v]; i < edge[v].size(); ++i) {
        int ed = edge[v][i];
        int u = to[ed];

        if (dist[u] == dist[v] + 1 && cap[ed] - flow[ed] >= up_flow) {
            int to_flow = push(u, min(cur_flow, cap[ed] - flow[ed]), up_flow);
            if (to_flow > 0) {
                flow[ed] += to_flow;
                flow[ed ^ 1] -= to_flow;
                return to_flow;
            }
        }
    }
    return 0;
}

inline int readInt() {
    char c = getchar();
    while (c <= 32) c = getchar();
    int ret = 0;
    while ('0' <= c && c <= '9') ret = ret * 10 + c - '0', c = getchar();
    return ret;
}

mt19937 rng(228);

int main() {
#if __APPLE__
    freopen("in.txt", "r", stdin);
#endif

    int n = readInt();
    int m = readInt();

    for (int i = 0; i < n; ++i) {
        int c = readInt();
        addEdge(s, i, c);
    }
    for (int i = 0; i < n; ++i) {
        int c = readInt();
        addEdge(i + n, t, c);
    }
    
    for (int i = 0; i < m; ++i) {
        int a = readInt() - 1;
        int b = readInt() - 1;
        addEdge(a, b + n, INF, true);
    }

    int ans_flow = 0;
    for (int up = 1 << 30; up >= 1; up >>= 1) {
        while (bfs(up)) {
            memset(first, 0, sizeof first);
            while (true) {
                int add = push(s, INF_FLOW, up);
                if (add == 0) break;
                ans_flow += add;
            }
        }
    }

    printf("%d\n", ans_flow);
}
