#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

struct Q {
    int l, r, q;
};

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    vector<Q> q(m);
    for (int i = 0; i < m; ++i) {
        scanf("%d%d%d", &q[i].l, &q[i].r, &q[i].q);
        --q[i].l, --q[i].r;
    }

    sort(q.begin(), q.end(), [](Q q1, Q q2) {return q1.q > q2.q;});

    vector<int> a(n, INF);
    for (int i = 0; i < m; ++i) {
        for (int j = q[i].l; j <= q[i].r; ++j) {
            a[j] = q[i].q;
        }
    }

    bool ok = true;
    for (int i = 0; i < m; ++i) {
        int mx = 0;
        for (int j = q[i].l; j <= q[i].r; ++j) {
            mx = max(mx, a[j]);
        }
        if (mx != q[i].q) {
            ok = false;
            break;
        }
    }

    if (ok) {
        puts("EASY");
        for (int x : a) {
            printf("%d ", x);
        }
        puts("");
    } else {
        puts("FAIL");
    }
}
