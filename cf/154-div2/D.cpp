#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 444;

int n, m, k;
int a[N][N];
int sum[N][N];

int get(int i1, int j1, int i2, int j2) {
  return sum[i2][j2] - sum[i1 - 1][j2] - sum[i2][j1 - 1] + sum[i1 - 1][j1 - 1];
}

int main() {
#if __APPLE__
  freopen("D.in", "r", stdin);
  freopen("D.out", "w", stdout);
#else
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif

  scanf("%d%d%d", &n, &m, &k);

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      char c;
      scanf(" %c", &c);
      a[i][j] = c - 'a';
    }
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + !a[i][j];
    }
  }

  ll ans = 0;
  for (int i1 = 1; i1 <= n; i1++) {
    for (int i2 = i1 + 1; i2 <= n; i2++) {
      int cnt[26];
      memset(cnt, 0, sizeof cnt);
      for (int j1 = 1, j2 = 1; j1 <= m; j1++) {
        if (j2 == j1) {
          if (a[i1][j2] == a[i2][j2]) {
            cnt[a[i1][j2]]++;
          }
          j2++;
        }
        if (a[i1][j1] == a[i2][j1]) {
          cnt[a[i1][j1]]--;
        }
        if (a[i1][j1] == a[i2][j1] && get(i1, j1, i2, j2 - 1) <= k) {
          ans += cnt[a[i1][j1]];
        }
        while (j2 <= m && get(i1, j1, i2, j2) <= k) {
          if (a[i1][j2] == a[i2][j2]) {
            cnt[a[i1][j2]]++;
            if (a[i1][j1] == a[i2][j1] && a[i1][j1] == a[i1][j2]) {
              ans++;
            }
          }
          j2++;
        }
      }
    }
  }

  printf("%lld\n", ans);
}
