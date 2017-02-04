#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Edge {
    int a, b, l, id;
};

const int N = 1e5;

int p[N], rnk[N];

int get(int v) {
    return p[v] == v ? v : p[v] = get(p[v]);
}

void unite(int v, int u) {
    v = get(v);
    u = get(u);
    if (v == u) return;
    if (rnk[v] < rnk[u]) swap(v, u);
    p[u] = v;
    if (rnk[v] == rnk[u]) rnk[v]++;
}

bool cmp(Edge e1, Edge e2) {
    return e1.l < e2.l;
}

int main() {
    freopen("jump.in", "r", stdin);
    freopen("jump.out", "w", stdout);

    int n, m, k, c;
    scanf("%d%d%d%d", &n, &m, &k, &c);

    for (int i = 0; i < n; i++) {
        p[i] = i;
    }

    vector<Edge> a(m);
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", &a[i].a, &a[i].b, &a[i].l);
        --a[i].a, --a[i].b;
        a[i].id = i;
    }

    sort(a.begin(), a.end(), cmp);

    int used[m];
    memset(used, 0, sizeof used);

    ll cursum = 0;
    vector<Edge> toban;
    for (int i = 0; i < m; i++) {
        int v = a[i].a;
        int u = a[i].b;
        int l = a[i].l;
        if (get(v) != get(u)) {
            cursum += l;
            unite(v, u);
            used[a[i].id] = 1;
            a[i].l = l * (c - 1);
            toban.push_back(a[i]);
        } else {
            a[i].l *= c;
            toban.push_back(a[i]);
        }
    }

    bool ok = true;
    int fath = get(0);
    for (int i = 1; i < n; i++) {
        if (get(i) != fath) {
            ok = false;
            break;
        }
    }

    if (!ok || cursum > k) {
        puts("Impossible");
    } else {
        sort(toban.begin(), toban.end(), cmp);
        for (int i = 0; i < (int)toban.size(); i++) {
            if (cursum + toban[i].l <= k) {
                cursum += toban[i].l;
                used[toban[i].id] = 2;
            }
        }
        vector<int> P, Q;
        for (int i = 0; i < m; i++) {
            if (used[i] == 1) P.push_back(i);
            if (used[i] == 2) Q.push_back(i);
        }

        printf("%d %d\n", (int)P.size(), (int)Q.size());
        for (int x : P) {
            printf("%d ", x + 1);
        }
        puts("");
        for (int x : Q) {
            printf("%d ", x + 1);
        }
        puts("");
    }
}
