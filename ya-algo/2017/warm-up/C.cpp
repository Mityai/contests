#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

const int INF = 1e9;

int main() {
#if __APPLE__
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif

    int n;
    scanf("%d", &n);

    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }
    a[0] = -1e9;

    sort(a.begin(), a.end());

    vector<int> dp(n + 1, INF);
    dp[0] = 0;
    for (int i = 1; i <= n; ++i) {
        dp[i] = dp[i - 1] + 1;
        if (a[i] - a[i - 1] <= 2) {
            dp[i] = min(dp[i], dp[i - 2] + 1);
        }
    }

    printf("%d\n", dp[n]);
}
