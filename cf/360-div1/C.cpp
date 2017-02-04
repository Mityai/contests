#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, k;
  scanf("%d%d", &n, &k);

  int c[n];
  for (int i = 0; i < n; i++) {
    scanf("%d", c + i);
  }

  bool can[k + 1];
  memset(can, 0, sizeof can);

  bool dp[k + 1][k + 1];
  memset(dp, 0, sizeof dp);

  can[0] = true;
  dp[0][0] = true;
  for (int i = 0; i < n; i++) {
    int x = c[i];
    for (int pr = k - x; pr >= 0; pr--) {
      int nw = pr + x;
      if (can[pr]) {
        can[nw] = true;
        dp[nw][0] = true;
        for (int sm = k; sm >= 0; sm--) {
          if (dp[pr][sm] == true) {
            dp[nw][sm] = true;
            if (sm + x <= k) {
              dp[nw][sm + x] = true;
            }
          }
        }
      }
    }
  }

  vector<int> ans;
  for (int i = 0; i <= k; i++) {
    if (dp[k][i]) ans.push_back(i);
  }

  printf("%d\n", (int)ans.size());
  for (int x : ans) {
    printf("%d ", x);
  }
  puts("");
}
