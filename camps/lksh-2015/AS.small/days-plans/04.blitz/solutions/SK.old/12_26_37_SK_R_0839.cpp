/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2012.07.03
 */

#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

const int maxN = 403;

int n, m, x[maxN], f[maxN][maxN];

int main()
{
  scanf("%d%d", &n, &m);
  forn(i, n)
    scanf("%d", &x[i]);
  memset(f, 0x70, sizeof(f));
  f[0][1] = 0;
  forn(i, n)
    forn(j, i + 2)
      for (int k = i + 1; k < n; k++)
        f[k][j + 1] = min(f[k][j + 1], max(f[i][j], x[k] - x[i]));
  printf("%d\n", f[n - 1][n - m]);
  return 0;
}
