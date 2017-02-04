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

int n;
ll treemax[4 * MAXN + 15];
ll bl[4 * MAXN + 15];
ll a[MAXN];

void relax(int v) {
    treemax[v] = max(treemax[2 * v + 1], treemax[2 * v + 2]);
}

void setVal(int v, ll x) {
    // if (v >= 4 * n) return;
    treemax[v] += x;
    bl[v] += x;
}

void push(int v) {
    if (bl[v] != 0) {
        setVal(2 * v + 1, bl[v]);
        setVal(2 * v + 2, bl[v]);
        bl[v] = 0;
    }
}

void buildTree(int v, int l, int r) {
    if (r - l == 1) {
        treemax[v] = a[l];
        return;
    }

    int m = (l + r) / 2;
    buildTree(2 * v + 1, l, m);
    buildTree(2 * v + 2, m, r);

    relax(v);
}

void addSeq(int v, int l, int r, const int &reql, const int &reqr, const ll &val) {
    if (r <= reql || reqr <= l) return;
    if (reql <= l && r <= reqr) {
        setVal(v, val);
        return;
    }

    push(v);
    int m = (l + r) / 2;
    addSeq(v * 2 + 1, l, m, reql, reqr, val);
    addSeq(v * 2 + 2, m, r, reql, reqr, val);

    relax(v);
}

ll getMax(int v, int l, int r, const int &reql, const int &reqr) {
    if (reqr <= l || r <= reql) return -INF;
    if (reql <= l && r <= reqr) return treemax[v];
    push(v);
    int m = (l + r) / 2;
    return max(getMax(2 * v + 1, l, m, reql, reqr), getMax(2 * v + 2, m, r, reql, reqr));
}

int main() {
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    buildTree(0, 0, n);

    int k;
    scanf("%d", &k);

    for (int i = 0; i < k; i++) {
        char c;
        cin >> c;

        if (c == 'm') {
            int l, r;
            cin >> l >> r;

            printf("%d ", getMax(0, 0, n, l - 1, r));
        } else {
            int l, r;
            ll x;
            cin >> l >> r >> x;

            addSeq(0, 0, n, l - 1, r, x);
        }
    }
}
