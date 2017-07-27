/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2012.02.12
 */

#include <ctime>
#include <cstdio>
#include <cassert>

#define NAME "semiplane"

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long long ll;

const int maxN = (int)1e5;

int n, m, x[maxN], y[maxN];

int main()
{
#ifdef DEBUG
  double tmp_start = clock();
  fprintf(stderr, "Start\n");
#endif

  assert(freopen(NAME ".in", "r", stdin));
  assert(freopen(NAME ".out", "w", stdout));

  scanf("%d%d%*d", &n, &m);
  forn(i, n)
    scanf("%d%d", &x[i], &y[i]);
  forn(i, m)
  {
    int a, b, c, cnt = 0;
    scanf("%d%d%d", &a, &b, &c);
    forn(j, n)
      cnt += ((ll)a * x[j] + (ll)b * y[j] + c >= 0);
    printf("%d\n", cnt);
  }

#ifdef DEBUG
  fprintf(stderr, "Total time = %.2lf\n", (clock() - tmp_start) / CLOCKS_PER_SEC);
#endif
  return 0;
}
