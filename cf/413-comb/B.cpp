#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

int main() {
#if __APPLE__
    //freopen("B.in", "r", stdin);
    //freopen("B.out", "w", stdout);
#endif

    int n;
    scanf("%d", &n);

    vector<multiset<pair<int, int>>> mincost(3);

    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &p[i]);
    }

    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
        --a[i];
    }
    for (int i = 0; i < n; ++i) {
        scanf("%d", &b[i]);
        --b[i];
    }

    for (int i = 0; i < n; ++i) {
        mincost[a[i]].insert({p[i], i});
        mincost[b[i]].insert({p[i], i});
    }

    int m;
    scanf("%d", &m);

    for (int i = 0; i < m; ++i) {
        int c;
        scanf("%d", &c);
        --c;

        if (mincost[c].empty()) {
            printf("-1 ");
        } else {
            int id = mincost[c].begin()->se;
            mincost[a[id]].erase({p[id], id});
            mincost[b[id]].erase({p[id], id});
            printf("%d ", p[id]);
        }
    }
    puts("");
}
