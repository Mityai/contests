/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2012.07.12
 */

#include <cstdio>
#include <cassert>

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

int main()
{
  #define NAME "joseph"
  assert(freopen(NAME ".in", "r", stdin));
  assert(freopen(NAME ".out", "w", stdout));
  
  int n, p, r = 0;
  scanf("%d%d", &n, &p);
  for (int i = 2; i <= n; i++)
    r = (p + r) % i;
  printf("%d\n", r + 1);
  return 0;
}
