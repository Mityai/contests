#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 555;
const int M = 12345;
const int M2 = 2 * M;
const ll INF = LLONG_MAX;

const int s = 0;
int t;

int n, m;
vector<int> E[N];
int to[M2], first[N], d[N];
ll flow[M2], cap[M2];

bool bfs(ll add_flow) {
    queue<int> q;
    q.push(s);

    memset(d, 127, sizeof d);
    const int INFd = d[0];
    d[s] = 0;
    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (int edge : E[v]) {
            int u = to[edge];
            if (d[u] == INFd && cap[edge] - flow[edge] >= add_flow) {
                q.push(u);
                d[u] = d[v] + 1;
            }
        }
    }
    return d[t] != INFd;
}

ll push(int v, ll cur_flow, ll add_flow) {
    if (v == t || cur_flow == 0) {
        return cur_flow;
    }

    for (int &i = first[v]; i < (int)E[v].size(); i++) {
        int e = E[v][i];
        int u = to[e];
        
        if (d[u] == d[v] + 1 && cap[e] - flow[e] >= add_flow) {
            ll to_flow = push(u, min(cur_flow, cap[e] - flow[e]), add_flow);
            if (to_flow > 0) {
                flow[e] += to_flow;
                flow[e ^ 1] -= to_flow;
                return to_flow;
            }
        }
    }
    return 0;
}

int e = 0;
void addEdge(int u, int v, ll c) {
    E[u].push_back(e);
    E[v].push_back(e ^ 1);

    cap[e] = c;
    cap[e ^ 1] = 0;

    to[e] = v;
    to[e ^ 1] = u;

    e += 2;
}

int main() {
#if __APPLE__
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
#else
    freopen("flow2.in", "r", stdin);
    freopen("flow2.out", "w", stdout);
#endif

    scanf("%d%d", &n, &m);
    t = n - 1;

    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        scanf("%d%d%lld", &u, &v, &w);
        addEdge(u - 1, v - 1, w);
    }

    ll ansFlow = 0;
    for (ll i = 1 << 29; i >= 1; i >>= 1) {
        while (bfs(i)) {
            memset(first, 0, sizeof first);
            while (true) {
                ll add = push(s, INF, i);
                if (add == 0) break;
                ansFlow += add;
            }
        }
    }
    printf("%lld\n", ansFlow);
}
