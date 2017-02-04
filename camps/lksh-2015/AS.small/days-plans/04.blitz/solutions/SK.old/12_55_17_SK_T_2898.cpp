/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2012.07.03
 */

#include <cstdio>
#include <cassert>
#include <algorithm>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

#ifdef _WIN32
#  define I64 "%I64d"
#else
#  define I64 "%lld"
#endif

int n, a[(int)1e6 + 10];
long long s1, s2;

int main()
{
  scanf("%d", &n);
  forn(i, n)
  {
    scanf("%d" ,&a[i]);
    if (a[i] < 0)
      s1 += -a[i];
    else
      s2 += a[i];
  }
  forn(i, n)
    if (a[i] > 0)
      printf(I64" ", s1);
    else
      printf(I64" ", s2);
  return 0;
}
