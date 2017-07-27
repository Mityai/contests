#include <bits/stdc++.h>
using namespace std;
const int INF = 1e6;
vector<int> to;
vector<int> cap;
int cnt = 0;
vector<vector<int>> e;
vector<bool> usededge;
vector<bool> used;
vector<int> was;
int t;
void add_edge(int v, int u, int c) {
    cap[cnt] = c;
    cap[cnt ^ 1] = c;
    e[v].push_back(cnt);
    e[u].push_back(cnt ^ 1);
    to[cnt] = u;
    to[cnt ^ 1] = v;
    cnt += 2;
}
 
int push(int v, int cur_flow, vector<int>&flow) {
    if (v == t || cur_flow == 0 ) {
        return cur_flow;
    }
    used[v] = true;
    for (auto edge : e[v]) {
        int u = to[edge];
        if (!used[u]) {
            int a = push(u, min(cap[edge] - flow[edge], cur_flow), flow);
            if (a > 0) {
                flow[edge] += a;
                flow[edge ^ 1] -= a;
                return a;
            }
        }
         
    }
    return 0;
}
 
void dfs(int v, vector<int> &flow) {
    was[v] = true;
    for (auto edge : e[v]) {
        int u = to[edge];
        if (!was[u] && cap[edge] - flow[edge] > 0) {
            dfs(u, flow);
        }
    }
}
 
int main() {
    int n, m;
    cin >> n >> m;
    int s = 0;
    t = n + n + 1;
    e.resize(n * 2 + 2);
    used.resize(n * 2 + 2);
    was.resize(n * 2 + 2);
    cap.resize(4 * n + 2 * m);
    to.resize(4 * n + 2 * m);
    vector<int> flow;
    vector<pair<pair<int, int>, int>> edg;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> b[i];//i + n
    }
    for (int i = 1; i <= n; ++i) {
        edg.push_back({{s, i}, a[i - 1]});
        edg.push_back({{i + n, t}, b[i - 1]});
        add_edge(s, i, a[i - 1]);
        add_edge(i + n, t, b[i - 1]);
    }
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        edg.push_back({{a, b + n}, INF});
        add_edge(a, b + n, INF);
    }
    flow.resize(cnt);
    int ansflow = 0;
    int cur_flow = 0;
    while ((cur_flow = push(0, 1e9, flow)) > 0) {
        ansflow += cur_flow;
        fill(used.begin(), used.end(), false);
    }
    dfs(0, flow);
    int best_cut = 0;
    vector<int> id;
    for (int i = 0; i < edg.size(); ++i) {
        auto e = edg[i];
        if (was[e.first.first] + was[e.first.second] == 1) {
            best_cut += e.second;
            id.push_back(i + 1);
        }
    }
    cout << best_cut;
    return 0;
}
