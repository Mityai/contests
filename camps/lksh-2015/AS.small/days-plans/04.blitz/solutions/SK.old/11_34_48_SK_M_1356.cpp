/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2012.07.03
 */

#include <cstdio>
#include <cassert>
#include <algorithm>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

int n, z[(int)1e5 + 10];
int main()
{
  scanf("%d", &n);
  forn(i, n)
    scanf("%d", &z[i]);

  int p = 0;
  forn(i, n)
  {
    while (p + z[p] <= i)
      p++;
    printf("%d ", i - p + 1);
  }
  return 0;
}
