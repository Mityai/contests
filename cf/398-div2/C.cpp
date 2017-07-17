#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

const int N = 1e6;

int n;
vector<int> g[N];
int w[N], tin[N], tout[N];
int need;
int timer = 0;
int st;
vector<int> p1, p2;

void go(int v) {
    tin[v] = timer++;
    for (int u : g[v]) {
        go(u);
        w[v] += w[u];
    }
    if (v != st && w[v] == need) {
        p1.push_back(v);
    }
    if (v != st && w[v] == 2 * need) {
        p2.push_back(v);
    }
    tout[v] = timer++;
}

bool cmp(int v, int u) {
    return tin[v] < tin[u];
}

void ans(int v, int u) {
    printf("%d %d\n", v + 1, u + 1);
    exit(0);
}

int main() {
#if __APPLE__
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif

    scanf("%d", &n);
    
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        int p;
        scanf("%d%d", &p, &w[i]);
        --p;
        if (p != -1) {
            g[p].push_back(i);
        } else {
            st = i;
        }
        sum += w[i];
    }

    if (abs(sum) % 3 != 0) {
        puts("-1");
        return 0;
    }

    need = sum / 3;
    go(st);

    sort(p1.begin(), p1.end(), cmp);
    sort(p2.begin(), p2.end(), cmp);

    if (p1.size() >= 2) {
        for (int v : p1) {
            if (tout[v] < tin[p1.back()]) {
                ans(v, p1.back());
            }
        }
    }
    for (int v : p2) {
        int lb = -1, rb = p1.size();
        while (lb + 1 < rb) {
            int mb = (lb + rb) / 2;
            if (tin[v] < tin[p1[mb]]) {
                rb = mb;
            } else {
                lb = mb;
            }
        }
        if (rb != p1.size()) {
            int u = p1[rb];
            if (tin[v] <= tin[u] && tout[u] <= tout[v]) {
                ans(v, u);
            }
        }
    }

    puts("-1");
}
