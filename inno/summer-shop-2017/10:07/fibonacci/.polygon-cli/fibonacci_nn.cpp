#include <cstdio>

int const N = 123;

int a[N][N], f[N], res[N][N], tmp[N][N], g[N];

int const MOD = 1000000007;

void add(int & a, int b) {
  a += b;
  if (a >= MOD) a -= MOD;
}

int mul(int a, int b) {
  return (long long) a * b % MOD;
}

int main() {
  freopen("fibonacci.in", "r", stdin);
  freopen("fibonacci.out", "w", stdout);
  int k;
  long long n;
  scanf("%d%I64d", &k, &n);
  for (int i = 0; i < k; i++) scanf("%d", f + i);
  for (int i = 0; i < k; i++) {
    scanf("%d", g + i);
  }
  for (int i = 0; i + 1 < k; i++) {
    a[i][i + 1] = 1;
  }
  for (int i = 0; i < k; i++) {
    a[k - 1][i] = g[k - i - 1];
  }
  a[k][k] = 1;
  a[k][0] = 1;
  for (int i = 0; i <= k; i++) res[i][i] = 1;
  while (n > 0) {
    if (n & 1) {
      for (int i = 0; i <= k; i++)
        for (int j = 0; j <= k; j++) {
          tmp[i][j] = 0;
          for (int e = 0; e <= k; e++)
            add(tmp[i][j], mul(res[i][e], a[e][j]));
        }
      for (int i = 0; i <= k; i++)
        for (int j = 0; j <= k; j++)
          res[i][j] = tmp[i][j];
    }
    for (int i = 0; i <= k; i++)
      for (int j = 0; j <= k; j++) {
        tmp[i][j] = 0;
        for (int e = 0; e <= k; e++)
          add(tmp[i][j], mul(a[i][e], a[e][j]));
      }
    for (int i = 0; i <= k; i++)
      for (int j = 0; j <= k; j++)
        a[i][j] = tmp[i][j];
    n >>= 1;
  }
  int ans = 0;
  int sum = 0;
  for (int i = 0; i <= k; i++)
    add(ans, mul(res[0][i], f[i]));
  for (int i = 0; i <= k; i++)
    add(sum, mul(res[k][i], f[i]));
  add(sum, ans);
  printf("%d %d\n", ans, sum);
}
