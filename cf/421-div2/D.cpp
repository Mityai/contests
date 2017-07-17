#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

int main() {
#if __APPLE__
    freopen("D.in", "r", stdin);
    freopen("D.out", "w", stdout);
#endif

    int n;
    scanf("%d", &n);

    vector<int> p(n + n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &p[i]);
        --p[i];
        p[i + n] = p[i];
    }

    int ans = 0, posans = 0;
    vector<vector<int>> st(n);
    int le = 0, ri = 0;
    for (int i = 0; i < n; ++i) {
        ans += abs(p[i] - i);
        if (p[i] <= i) {
            ++ri;
            st[i - p[i]].push_back(i);
        } else {
            ++le;
            st[i + n - p[i]].push_back(i);
        }
    }

    int best = ans;
    for (int i = 1; i < n; ++i) {
        if (p[i - 1] != 0) {
            --ri;
        } else {
            --le;
        }

        ans -= p[i - 1];
        ans += le;
        ans -= ri;
        ans += n - p[i - 1];

        if (ans < best) {
            best = ans;
            posans = i;
        }

        for (int id : st[i]) {
            int x = p[id];
            if (x == p[i - 1]) continue;
            int f = i + x;
            --le;
            ++ri;
        }

        if (p[i - 1] != n - 1) {
            ++le;
        } else {
            ++ri;
        }
    }

    printf("%d %d\n", best, n - posans);
}
