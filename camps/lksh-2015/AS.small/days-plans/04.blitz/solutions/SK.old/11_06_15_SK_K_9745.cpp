/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2012.07.03
 */

#include <cstdio>
#include <cassert>
#include <algorithm>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

int main()
{
  int x1, x2, y1, y2;
  scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
  x2 -= x1, y2 -= y1;
  if (!x2 && !y2)
    printf("%d\n", 0);
  else
    printf("%d\n", __gcd(x2, y2) + 1);
  return 0;
}
