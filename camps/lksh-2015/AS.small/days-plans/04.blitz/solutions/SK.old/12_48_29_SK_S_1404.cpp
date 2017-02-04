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
  int x1, y1, x2, y2, h;
  scanf("%d%d%*d", &x1, &y1);
  scanf("%d%d%d", &x2, &y2, &h);

  double X = h + abs(y2 - y1);
  double Y = abs(x2 - x1);
  printf("%.20f\n", sqrt(X * X + Y * Y));
  return 0;
}
