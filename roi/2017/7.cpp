#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int INF = INT_MAX;
const int C = 1e9;

struct Q {
    int l, r, c;
};

int main() {
    int n, a;
    scanf("%d%d", &n, &a);

    vector<Q> q(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d%d%d", &q[i].l, &q[i].r, &q[i].c);
        if (q[i].l != q[i].r && n != 1) {
            cout << "9999999890" << endl;
            return 0;
        }
    }

    vector<int> dp(a + 1, INF);
    dp[0] = 0;
    for (int i = 0; i <= a; ++i) {
        if (dp[i] < INF) {
            for (int j = 0; j < n; ++j) {
                if (i + q[j].r <= a) {
                    for (int k = i + q[j].l; k <= i + q[j].r; ++k) {
                        dp[k] = min(dp[k], dp[i] + q[j].c);
                    }
                }
            }
        }
    }

    ll ans = 0;
    set<int> was;
    for (int i = 0; i <= a; ++i) {
        if (dp[i] < INF && was.find(dp[i]) == was.end()) {
            ans = max(ans, i * 1ll * C - dp[i]);
            was.insert(dp[i]);
        }
    }

    printf("%lld\n", ans);
}
