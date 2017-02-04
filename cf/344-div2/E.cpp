#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

int main() {
#if __APPLE__
    freopen("E.in", "r", stdin);
    freopen("E.out", "w", stdout);
#endif

    int n, m;
    scanf("%d%d", &n, &m);

    int a[n];
    int b[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        b[i] = a[i];
    }

    vector< pair<int, int> > q;
    for (int i = 0; i < m; i++) {
        int t, r;
        scanf("%d%d", &t, &r);

        while (!q.empty() && q.back().se <= r - 1) {
            q.pop_back();
        }
        q.push_back({t, r - 1});
    }

    reverse(q.begin(), q.end());

    multiset<int> s;
    for (int i = 0; i <= q.back().se; i++) {
        s.insert(a[i]);
    }

    for (int i = (int)q.size() - 1; i >= 0; i--) {
        for (int j = q[i].se; j > (i > 0 ? q[i - 1].se : -1); j--) {
            if (q[i].fi == 1) {
                b[j] = *s.rbegin();
                s.erase(--s.end());
            } else {
                b[j] = *s.begin();
                s.erase(s.begin());
            }
        }
    }

    for (int i = 0; i < n; i++) {
        printf("%d ", b[i]);
    }
    puts("");
}
