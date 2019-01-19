#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 1e5;

int fenw[N + 1];
int n;

void add(int pos, int val) {
    for (int i = pos; i < n; i = (i | (i + 1))) {
        fenw[i] += val;
    }
}

int sum(int pos) {
    int res = 0;
    for (int i = pos; i >= 0; i = (i & (i + 1)) - 1) {
        res += fenw[i];
    }
    return res;
}

int main() {
#if __APPLE__
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif

    while (scanf("%d", &n) == 1) {
        memset(fenw, 0, sizeof(int) * (n + 1));

        vector<int> a(n);
        int mxi = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%d", &a[i]);
            if (a[i] > a[mxi]) {
                mxi = i;
            }
        }

        ll ans = 0;

        int marks = a[mxi] + 1;
        vector<char> was(n + 1, true);
        for (int i = 0; i < marks; ++i) {
            add(i, 1);
            was[i] = false;
        }
        for (int i = mxi; i >= 0; --i) {
            int lb = -1, rb = n;
            while (lb + 1 < rb) {
                int mb = (lb + rb) / 2;
                if (sum(mb) <= a[i]) {
                    lb = mb;
                } else {
                    rb = mb;
                }
            }
            if (!was[rb]) {
                add(rb, -1);
                was[rb] = true;
            }
            ans += sum(n) - sum(rb);
        }

        for (int i = mxi + 1; i < n; ++i) {
            ans += marks - a[i] - 1;
        }

        printf("%lld\n", ans);
    }
}
