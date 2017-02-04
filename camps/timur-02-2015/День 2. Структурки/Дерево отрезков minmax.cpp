#include <bits/stdc++.h>

#define mp make_pair
#define fi first
#define se second

using namespace std;

typedef long long ll;

const int INF = 1234657890;
const int MAXN = 1e5;
const ll MOD1 = 12345;
const ll MOD2 = 23456;

const int n = MAXN;

int treemin[4 * MAXN + 15], treemax[4 * MAXN + 15];

int getVal(int n) {
    ll k = (ll)n;
    int res = int((k * k) % MOD1 + (k * k * k) % MOD2);
    return res;
}

void relax(int v) {
    treemin[v] = min(treemin[2 * v + 1], treemin[2 * v + 2]);
    treemax[v] = max(treemax[2 * v + 1], treemax[2 * v + 2]);
}

void buildTree(int v, int l, int r) {
    if (r - l == 1) {
        int x = getVal(l + 1);
        treemin[v] = x;
        treemax[v] = x;
        return;
    }

    int m = (l + r) / 2;
    buildTree(2 * v + 1, l, m);
    buildTree(2 * v + 2, m, r);

    relax(v);
}

void update(int v, int l, int r, const int &pos, const int &val) {
    if (r <= pos || pos < l) return;
    if (r - l == 1) {
        treemin[v] = val;
        treemax[v] = val;
        return;
    }

    int m = (l + r) / 2;
    update(v * 2 + 1, l, m, pos, val);
    update(v * 2 + 2, m, r, pos, val);

    relax(v);
}

int getMin(int v, int l, int r, const int &reql, const int &reqr) {
    if (reqr <= l || r <= reql) return INF;
    if (reql <= l && r <= reqr) return treemin[v];
    int m = (l + r) / 2;
    return min(getMin(2 * v + 1, l, m, reql, reqr), getMin(2 * v + 2, m, r, reql, reqr));
}

int getMax(int v, int l, int r, const int &reql, const int &reqr) {
    if (reqr <= l || r <= reql) return -INF;
    if (reql <= l && r <= reqr) return treemax[v];
    int m = (l + r) / 2;
    return max(getMax(2 * v + 1, l, m, reql, reqr), getMax(2 * v + 2, m, r, reql, reqr));
}

int main() {
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    buildTree(0, 0, n);

    int k;
    scanf("%d", &k);

    for (int i = 0; i < k; i++) {
        int x, y;
        scanf("%d%d", &x, &y);

        if (x < 0) {
            update(0, 0, n, -x - 1, y);
        } else {
            int minReq = getMin(0, 0, n, x - 1, y);
            int maxReq = getMax(0, 0, n, x - 1, y);
            printf("%d\n", maxReq - minReq);
        }
    }
}
