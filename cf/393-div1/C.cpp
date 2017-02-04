#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

const int N = 1e5;

int sum[4 * N], bal[4 * N];
int xval[N];

void setval(int v, int l, int r, int pos, int val) {
    if (r - l == 1) {
        sum[v] = bal[v] = val;
        return;
    }
    int m = (l + r) / 2;
    if (pos < m) setval(v * 2 + 1, l, m, pos, val);
    else setval(v * 2 + 2, m, r, pos, val);
    sum[v] = sum[v * 2 + 1] + sum[v * 2 + 2];
    bal[v] = max(bal[v * 2 + 2], bal[v * 2 + 1] + sum[v * 2 + 2]);
}

int get_ans(int v, int l, int r, int sumright) {
    if (r - l == 1) {
        return xval[l];
    }
    int m = (l + r) / 2;
    if (bal[2 * v + 2] + sumright > 0) {
        return get_ans(v * 2 + 2, m, r, sumright);
    }
    return get_ans(v * 2 + 1, l, m, sumright + sum[v * 2 + 2]);
}

int main() {
#if __APPLE__
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif

    int n;
    while (scanf("%d", &n) == 1) {
        for (int i = 0; i < n; ++i) {
            int p, t;
            scanf("%d%d", &p, &t);
            if (t == 1) {
                scanf("%d", &xval[p - 1]);
                setval(0, 0, n, p - 1, 1);
            } else {
                setval(0, 0, n, p - 1, -1);
            }

            if (bal[0] <= 0) {
                printf("-1\n");
            } else {
                printf("%d\n", get_ans(0, 0, n, 0));
            }
        }
    }
}
