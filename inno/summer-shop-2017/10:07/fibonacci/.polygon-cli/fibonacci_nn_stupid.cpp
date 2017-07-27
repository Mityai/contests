#include <cstdio>

int const N = 5234567;

int f[N], g[N];

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
  for (int i = 0; i < k; i++) scanf("%d", g + i);
  for (int i = k; i <= n; i++) {
    for (int j = 0; j < k; j++) {
      add(f[i], mul(g[j], f[i - j - 1]));
    }
  }
  int ans = 0;
  for (int i = 0; i <= n; i++) add(ans, f[i]);
  printf("%d %d\n", f[n], ans);
}