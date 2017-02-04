/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2012.07.03
 */

#include <cstdio>
#include <cmath>
#include <cassert>
#include <algorithm>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

#ifdef _WIN32
#  define I64 "%I64d"
#else
#  define I64 "%lld"
#endif

int main()
{
  int n, x;
  scanf("%d", &n);
  forn(i, 5)
  {
    x = sqrt(n);
    n -= x * x;
    printf("%d ", x);
  }
  for (int a = 0; a * a <= n; a++)
    for (int b = 0; b <= a && a * a + b * b <= n; b++)
      for (int c = 0; c <= b && c * c + a * a + b * b <= n; c++)
        for (int d = 0; d <= c && d * d + c * c + a * a + b * b <= n; d++)
        {
          if (a * a + b * b + c * c + d * d == n)
          {
            printf("%d %d %d %d\n", a, b, c, d);
            return 0;
          }
        }
  return 0;
}
