#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

int main() {
#if __APPLE__
    freopen("D.in", "r", stdin);
    freopen("D.out", "w", stdout);
#endif

    int n, m;
    scanf("%d%d", &n, &m);

    vector<int> d(n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &d[i]);
    }

    vector<int> a(m + 1);
    for (int i = 1; i <= m; i++) {
        scanf("%d", &a[i]);
    }

    int lb = 0, rb = n + 1;
    while (lb + 1 < rb) {
        int mb = (lb + rb) / 2;
        vector<int> lastday(m + 1, -1);
        for (int i = 0; i < mb; i++) {
            lastday[d[i]] = i;
        }
        vector<pair<int, int>> sorted;
        for (int i = 1; i <= m; i++) {
            sorted.push_back({lastday[i], i});
        }
        sort(sorted.begin(), sorted.end());
        bool ok = true;
        vector<int> dd(mb);
        for (int i = 1; i <= m; i++) {
            if (lastday[i] != -1)
                dd[lastday[i]] = -i;
        }
        auto f = a;
        for (int i = 0, j = 0; i < mb; i++) {
            if (dd[i] != 0) continue;
            while (j < sorted.size() && f[sorted[j].se] == 0) j++;
            if (j < sorted.size()) {
                dd[i] = sorted[j].se;
                if (--f[sorted[j].se] == 0) {
                    ++j;
                }
            }
        }
        vector<int> cnt(m + 1);
        int got = 0;
        for (int i = 0; i < mb; i++) {
            if (dd[i] < 0) {
                int t = -dd[i];
                if (cnt[t] != a[t]) {
                    ok = false;
                    break;
                } else ++got;
            } else {
                cnt[dd[i]]++;
            }
        }
        if (ok && got == m) rb = mb;
        else lb = mb;
    }
    if (rb == n + 1) {
        rb = -1;
    }
    printf("%d\n", rb);
}
