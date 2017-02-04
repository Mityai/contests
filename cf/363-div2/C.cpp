#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
#if __APPLE__
  freopen("C.in", "r", stdin);
  freopen("C.out", "w", stdout);
#endif

  int n;
  while (cin >> n) {
    int a[n];
    for (int i = 0; i < n; i++) {
      cin >> a[i];
    }

    int dp[n][3];
    memset(dp, 127, sizeof dp);

    dp[0][0] = 1;
    dp[0][1] = !((a[0] == 1) || (a[0] == 3));
    dp[0][2] = !((a[0] == 2) || (a[0] == 3));

    for (int i = 1; i < n; i++) {
      if (a[i] == 0) {
        dp[i][0] = min(dp[i - 1][0], min(dp[i - 1][1], dp[i - 1][2])) + 1;
      } else if (a[i] == 1) {
        dp[i][0] = min(dp[i - 1][0], min(dp[i - 1][1], dp[i - 1][2])) + 1;
        dp[i][1] = min(dp[i - 1][0], dp[i - 1][2]);
      } else if (a[i] == 2) {
        dp[i][0] = min(dp[i - 1][0], min(dp[i - 1][1], dp[i - 1][2])) + 1;
        dp[i][2] = min(dp[i - 1][0], dp[i - 1][1]);
      } else if (a[i] == 3) {
        dp[i][1] = min(dp[i - 1][0], dp[i - 1][2]);
        dp[i][2] = min(dp[i - 1][0], dp[i - 1][1]);
      }
    }

    printf("%d\n", min(dp[n - 1][0], min(dp[n - 1][1], dp[n - 1][2])));
  }
}
