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
  while (scanf("%d", &n) == 1) {
    int a[n + 1];
    a[0] = 0;
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
    }

    bool f[n + 1][n + 1];
    memset(f, 0, sizeof f);

    for (int i = 1; i <= n; i++) {
      f[i][i] = true;
    }

    for (int i = 1; i + 1 <= n; i++) {
      f[i][i + 1] = (a[i] == a[i + 1]);
    }

    int sm[n + 1];
    partial_sum(a, a + n + 1, sm);
    
    for (int len = 2; len < n; len++) {
      for (int i = 1; i + len <= n; i++) {
        int j = i + len;

        for (int k = i, z = j; k + 1 < z; k++) {
          int sum1 = sm[k] - sm[i - 1];
          while (k < z && sum1 > sm[j] - sm[z - 1]) {
            z--;
          }
          int sum2 = sm[j] - sm[z - 1];
          if (k + 1 < z && sum1 == sum2 && f[i][k] && f[k + 1][z - 1] && f[z][j]) {
            f[i][j] = true;
          }
        }

        for (int k = i; k < j; k++) {
          if (f[i][k] && f[k + 1][j] && sm[k] - sm[i - 1] == sm[j] - sm[k]) {
            f[i][j] = true;
          }
        }

      }
    }

    int ans = a[1];
    for (int i = 1; i <= n; i++) {
      for (int j = i; j <= n; j++) {
        if (f[i][j]) {
          int cur = sm[j] - sm[i - 1];
          ans = max(ans, cur);
        }
      }
    }

    printf("%d\n", ans);
  }
}
