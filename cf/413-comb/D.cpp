#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

const int K = 35;
const int M = 1e5;
const int INF = 1e7;

int solve(ll a, ll b, ll h, ll w, const vector<ll>& q) {
    int n = q.size();
    vector<vector<int>> dp(n + 1, vector<int>(M + 1));
    dp[0][h] = w;
    for (int i = 0; i < n; ++i) {
        for (ll prev = 0; prev <= M; ++prev) {
            if (dp[i][prev] != 0) {
                int nx = min(M * 1ll, prev * q[i]);
                dp[i + 1][nx] = max(dp[i + 1][nx], dp[i][prev]);
                int ny = min(M * 1ll, dp[i][prev] * q[i]);
                dp[i + 1][prev] = max(dp[i + 1][prev], ny);
            }
        }
    }
    for (int i = 0; i <= n; ++i) {
        for (int j = a; j <= M; ++j) {
            if (dp[i][j] >= b) {
                return i;
            }
        }
    }
    return INF;
}

int main() {
#if __APPLE__
    freopen("D.in", "r", stdin);
    freopen("D.out", "w", stdout);
#endif

    ll a, b, h, w;
    int n;
    while (scanf("%lld%lld%lld%lld%d", &a, &b, &h, &w, &n) == 5) {

    vector<ll> q(n);
    for (int i = 0; i < n; ++i) {
        scanf("%lld", &q[i]);
    }

    sort(q.rbegin(), q.rend());
    q.resize(min((int)q.size(), K));
    int ans = min(solve(a, b, h, w, q), solve(b, a, h, w, q));
    if (ans == INF) {
        ans = -1;
    }

    printf("%d\n", ans);
    }
}
