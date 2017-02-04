/** OK, 0.108 sec */

#include <cstdio>
#include <cstdlib>
#include <cstring>

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

const int maxn = 10010;

int sum, n, A, x[maxn], f[maxn * 2], is[maxn]; // 160 K

int main()
{
  freopen("nearest.in", "r", stdin);
  freopen("nearest.out", "w", stdout);

  scanf("%d%d", &n, &A);
  forn(i, n)
    scanf("%d", &x[i]), sum += x[i];

  memset(f, -1, sizeof(f));
  f[maxn + x[0]] = 0;
  int S = abs(x[0]);
  for (int i = 1; i < n; i++)
  {
    for (int j = maxn - S; j <= maxn + S; j++)
      if (f[j] != -1 && f[j] != i && f[j + x[i]] == -1)
        f[j + x[i]] = i;
    S += abs(x[i]);
  }

  int opt = -1, func = -1;
  forn(j, maxn * 2)
  {
    #define F(j) abs((2 * ((j) - maxn) - sum) - A)
    if (f[j] != -1 && F(j) < F(opt))
      opt = j, func = 2 * ((j) - maxn) - sum;
  }

  while (opt != maxn + x[0])
    is[f[opt]] = 1, opt -= x[f[opt]];
  printf("%d\n%d", func, x[0]);
  for (int i = 1; i < n; i++)
    printf("%c%d", "-+"[is[i]], x[i]);
  return 0;
}
