#include <iostream>
#include <queue>
#include <vector>
#include <cstdio>
#define fi first
#define se second
using namespace std;

typedef long long ll;

const int INF = 1000;

const int N = 50;
const int M = 50;

vector<int> edge[N];

int dist[N];
int flow[M + M], cap[M + M], to[M + M];
int first[N];

int e = 0;

const int s = N - 1;
const int t = N - 2;

int addEdge(int u, int v, int c) {
    to[e] = v;
    to[e ^ 1] = u;

    cap[e] = c;
    cap[e ^ 1] = 0;

    edge[u].push_back(e);
    edge[v].push_back(e ^ 1);

    e += 2;
    return e - 2;
}

bool bfs(int up_flow) {
    fill(dist, dist + N, INF);

    dist[s] = 0;
    queue<int> q({s});
    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (int ed : edge[v]) {
            int u = to[ed];
            if (dist[u] == INF && cap[ed] - flow[ed] >= up_flow) {
                dist[u] = dist[v] + 1;
                q.push(u);
            }
        }
    }
    return dist[t] != INF;
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


void solve(int F, int P) {
    memset(cap, 0, sizeof cap);
    memset(flow, 0, sizeof flow);
    memset(to, 0, sizeof to);
    for (int i = 0; i < N; ++i) edge[i].clear();

    vector<int> eds(F), edf(F);
    for (int i = 0; i < F; ++i) {
        eds[i] = addEdge(s, i + 4, INF);
        edf[i] = addEdge(i, t, INF);
    }
    for (int i = 0; i < P; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        --u, --v;
        addEdge(u, v);
    }
}

int main() {
#if __APPLE__
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif

    int TEST;
    scanf("%d", &TEST);

    for (int test = 1; test <= TEST; ++test) {
        int F, P;
        scanf("%d%d", &F, &P);
        printf("Case #%d: ", test);
        solve(F, P);
    }
}
