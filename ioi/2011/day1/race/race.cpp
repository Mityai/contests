#include "grader.h"
#include <bits/stdc++.h>

#define fi first
#define se second

using namespace std;

typedef long long ll;

const int N = 2e5;
const int K = 1e6 + 1;
const int INF = 1e9;

vector< pair<int, int> > g[N];
int sz[N], father[N], depth[N], best1[K + 1], best2[K + 1], num1[K + 1], num2[K + 1];
ll dist[N];
bool used[N];
int T = 0;
int ans = INF;

void calcsz(int v, int p) {
    sz[v] = 1;
    for (auto to : g[v]) {
        int u = to.fi;
        if (u == p) continue;
        if (used[u]) continue;
        calcsz(u, v);
        sz[v] += sz[u];
    }
}

int getcentroid(int v, int p, int full) {
    for (auto to : g[v]) {
        int u = to.fi;
        if (u == p) continue;
        if (used[u]) continue;
        if (sz[u] > full / 2) {
            return getcentroid(u, v, full);
        }
    }
    return v;
}

vector<int> del;

void go(int v, int p, int d, int len, int k, int s) {
    del.push_back(d);
    if (best1[d] >= len) {
        if (num1[d] != s) {
            best2[d] = best1[d];
            num2[d] = num1[d];
        }
        best1[d] = len;
        num1[d] = s;
    } else if (best2[d] > len && num1[d] != s) {
        best2[d] = len;
        num2[d] = s;
    }
    int i = d, j = k - d;
    int cur = INF;
    if (num1[i] != num1[j]) {
        cur = best1[i] + best1[j];
    }
    if (num1[i] != num2[j]) {
        cur = min(cur, best1[i] + best2[j]);
    }
    if (num2[i] != num1[j]) {
        cur = min(cur, best2[i] + best1[j]);
    }
    if (num2[i] != num2[j]) {
        cur = min(cur, best2[i] + best2[j]);
    }
    if (i == k) {
        cur = min(cur, best1[i]);
    }
    ans = min(ans, cur);
    for (auto to : g[v]) {
        int u = to.fi;
        int w = to.se;
        if (u == p) continue;
        if (used[u]) continue;
        if (d + w <= k) {
            go(u, v, d + w, len + 1, k, s);
        }
    }
}

void decompose(int v, int k, int p = -1) {
    calcsz(v, v);
    int centroid = getcentroid(v, v, sz[v]);
    if (p == -1) father[centroid] = centroid;
    else father[centroid] = p;
    used[centroid] = true;

    //printf("cetroid = %d\n", centroid);

    for (int x : del) {
        best1[x] = best2[x] = num1[x] = num2[x] = INF;
    }
    del.clear();

    for (auto to : g[centroid]) {
        int u = to.fi;
        if (!used[u] && to.se <= k) {
            go(u, centroid, to.se, 1, k, u);
        }
    }

    for (auto to : g[centroid]) {
        int u = to.fi;
        if (!used[u]) {
            decompose(u, k, centroid);
        }
    }
}

int best_path(int n, int k, int H[][2], int L[]) {
    for (int i = 0; i < n - 1; i++) {
        int a = H[i][0], b = H[i][1], w = L[i];
        g[a].push_back({b, w});
        g[b].push_back({a, w});
    }

    fill(best1, best1 + k + 1, INF);
    fill(best2, best2 + k + 1, INF);
    fill(num1, num1 + k + 1, INF);
    fill(num2, num2 + k + 1, INF);

    decompose(0, k);

    if (ans == INF) return -1;
    return ans;
}
