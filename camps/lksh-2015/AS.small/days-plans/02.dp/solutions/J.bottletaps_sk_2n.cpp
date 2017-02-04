/** OK, 0.563 sec */

#include <cstdio>
#include <cassert>
#include <algorithm>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

const int maxn = 20;
const int maxm = 100 + maxn;

int End, n, a[maxn];
int m, p[maxm], pr[maxm];
int f[1 << maxn];

int readSet()
{
  int k, a, pr = 0;
  scanf("%d", &k);
  while (k--)
    scanf("%d", &a), pr |= 1 << (a - 1);
  return pr;
}

int main()
{
  #define NAME "bottletaps"
  assert(freopen(NAME ".in", "r", stdin));
  assert(freopen(NAME ".out", "w", stdout));

  scanf("%d", &n);
  forn(i, n)
    scanf("%d", &a[i]);
  scanf("%d", &m);
  forn(i, m)
    scanf("%d", &p[i]), pr[i] = readSet();
  End = readSet();
  forn(i, n)
    pr[m] = 1 << i, p[m++] = a[i];

  f[End] = 0;
  for (int i = End - 1; i >= 0; i ? i--, i &= End : i--) {
    f[i] = (int)1e9;
    forn(j, m)
      f[i] = min(f[i], f[(i | pr[j]) & End] + p[j]);
  }
  printf("%d\n", f[0]);
  return 0;
}
