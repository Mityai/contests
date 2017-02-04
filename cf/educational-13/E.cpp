#include <bits/stdc++.h>
using namespace std;

int main() {
#if __APPLE__
  freopen("E.in", "r", stdin);
#endif

  int n;
  cin >> n;

  if (n == 1) {
    cout << 1 << endl;
    return 0;
  }

  double p[n][n];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> p[i][j];
    }
  }

  int N = (1 << n);
  double dp[N][n];
  memset(dp, 1, sizeof dp);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i != j) {
        int mask = (1 << j);
        dp[mask][i] = p[i][j];
      }
    }
  }

  vector< vector<int> > masks(n + 1);
  for (int msk = 0; msk < N; msk++) {
    masks[__builtin_popcount(msk)].push_back(msk);
  }

  for (int popcnt = 1; popcnt < n; popcnt++) {
    for (int mask : masks[popcnt]) {
      if (popcnt > 1) {
        for (int i = 0; i < n; i++) {
          dp[mask][i] = 1 - dp[mask][i];
          bitset<4> sk = mask;
          cout << sk << ' ' << i << ' ' << dp[mask][i] << endl;
        }
      }
      for (int pr = 0; pr < n; pr++) {
        if (!((mask >> pr) & 1)) {
          for (int nx = 0; nx < n; nx++) {
            if (nx != pr) {
              if (!((mask >> nx) & 1)) {
                int newmask = mask | (1 << pr);
                dp[newmask][nx] *= dp[mask][pr] * p[pr][nx];
              }
            }
          }
        }
      }
    }
  }

  double ans = dp[N - 2][0];

  printf("%.10lf\n", ans);
}
