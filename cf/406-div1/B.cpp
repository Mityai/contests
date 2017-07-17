#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll INF = 1e16;
const int N = 1e5;

vector<pair<int, int>> g[4 * N];

int par[4 * N];
int tree[4 * N];
vector<int> leafs;

void build(int v, int L, int R) {
    par[v] = (v - 1) / 2;
    if (R - L == 1) {
        leafs.push_back(v);
        return;
    }
    // g[v].push_back({v * 2 + 1, 0});
    // g[v].push_back({v * 2 + 2, 0});
    int M = (L + R) / 2;
    build(v * 2 + 1, L, M);
    build(v * 2 + 2, M, R);
}

void get_fund(int v, int L, int R, int qL, int qR, vector<int>& fund) {
    if (qR <= L || R <= qL) return;
    if (qL <= L && R <= qR) {
        fund.push_back(v);
        return;
    }
    int M = (L + R) / 2;
    get_fund(v * 2 + 1, L, M, qL, qR, fund);
    get_fund(v * 2 + 2, M, R, qL, qR, fund);
}

int main() {
    int n, q, s;
    scanf("%d%d%d", &n, &q, &s);
    --s;

    build(0, 0, n);

    vector<int> aba;
    get_fund(0, 0, n, 0, 1, aba);
    for (int i = 0; i < q; ++i) {
        int t;
        scanf("%d", &t);

        vector<int> x, y;
        int w;
        if (t == 1) {
            int v, u;
            scanf("%d%d%d", &v, &u, &w);
            --v, --u;
            get_fund(0, 0, n, v, v + 1, x);
            get_fund(0, 0, n, u, u + 1, y);
        } else if (t == 2) {
            int v, l, r;
            scanf("%d%d%d%d", &v, &l, &r, &w);
            --v, --l;
            get_fund(0, 0, n, v, v + 1, x);
            get_fund(0, 0, n, l, r, y);
        } else if (t == 3) {
            int v, l, r;
            scanf("%d%d%d%d", &v, &l, &r, &w);
            --v, --l;
            get_fund(0, 0, n, l, r, x);
            get_fund(0, 0, n, v, v + 1, y);
        }
        for (int a : x) {
            for (int b : y) {
                g[a].push_back({b, w});
            }
        }
    }

    vector<ll> dist(4 * N, INF);
    set<pair<ll, int>> qe;
    qe.insert({dist[leafs[s]] = 0, leafs[s]});
    while (!qe.empty()) {
        int v = qe.begin()->second;
        qe.erase(qe.begin());

        {
            int x = par[v];
            while (x != par[x]) {
                if (dist[x] > dist[v]) {
                    qe.erase({dist[x], x});
                    dist[x] = dist[v];
                    qe.insert({dist[x], x});
                }
                x = par[x];
            }
        }

        for (auto& to : g[v]) {
            int u = to.first;
            int w = to.second;
            int x = par[u];
            while (x != par[x]) {
                if (dist[u] > dist[x]) {
                    qe.erase({dist[u], u});
                    dist[u] = dist[x];
                    qe.insert({dist[u], u});
                }
                x = par[x];
            }
            if (dist[u] > dist[v] + w) {
                qe.erase({dist[u], u});
                dist[u] = dist[v] + w;
                qe.insert({dist[u], u});
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        int x = leafs[i];
        if (dist[x] == INF) dist[x] = -1;
        printf("%lld ", dist[x]);
    }
    puts("");
}
