#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll INF = 1e5;

ll sqr(ll x) {
    return x * x;
}

ll dist(ll x1, ll y1, ll z1, ll x2, ll y2, ll z2) {
    return sqr(x1 - x2) + sqr(y1 - y2) + sqr(z1 - z2);
}

struct B {
    int i, j;
    double r;
};

int main() {
#if __APPLE__
    freopen("in", "r", stdin);
#endif

    int m, n, k;
    scanf("%d%d%d", &m, &n, &k);

    int a[m][n];
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &a[i][j]);
        }
    }

    vector<B> b(k);
    vector<vector<char>> used(m, vector<char>(n, false));
    for (int i = 0; i < k; ++i) {
        scanf("%d%d%lf", &b[i].i, &b[i].j, &b[i].r);
        --b[i].i, --b[i].j;
        used[b[i].i][b[i].j] = true;
    }

    ll ans = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (used[i][j]) continue;
            int minh = a[i][j], maxh = INF;
            for (auto& q : b) {
                int midh = max(a[q.i][q.j], a[i][j]);
                if (dist(i, j, midh, q.i, q.j, a[q.i][q.j]) > q.r * q.r) {
                    maxh = minh - 1;
                    break;
                }
                int lb = midh, rb = INF;
                while (lb + 1 < rb) {
                    int mb = (lb + rb) / 2;
                    if (dist(i, j, mb, q.i, q.j, a[q.i][q.j]) <= q.r * q.r) {
                        lb = mb;
                    } else {
                        rb = mb;
                    }
                }
                int curmax = lb;
                lb = a[i][j] - 1, rb = midh;
                while (lb + 1 < rb) {
                    int mb = (lb + rb) / 2;
                    if (dist(i, j, mb, q.i, q.j, a[q.i][q.j]) <= q.r * q.r) {
                        rb = mb;
                    } else {
                        lb = mb;
                    }
                }
                int curmin = rb;
                maxh = min(maxh, curmax);
                minh = max(minh, curmin);
                if (maxh < minh) break;
            }
            if (maxh < minh) continue;
            ans += maxh - minh + 1;
        }
    }

    printf("%lld\n", ans);
}
