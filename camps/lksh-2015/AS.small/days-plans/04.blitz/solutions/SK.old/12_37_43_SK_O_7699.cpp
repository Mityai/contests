/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2012.07.03
 */

#include <cstdio>
#include <cassert>
#include <algorithm>
#include <map>

using namespace std;

#ifdef _WIN32
#  define I64 "%I64d"
#else
#  define I64 "%lld"
#endif

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define mp make_pair

typedef long long ll;

map <pair<int,int>, ll> m;

ll f( int a, int b )
{
  if (a <= 2)
    return 1;
  if (2 * b > a)
    b = a + 1 - b;

  ll &r = m[mp(a, b)];
  if (2 * b == a + 1)
    r = (f(a - 1, b - 1) * f(a - 1, b) + 1) / f(a - 2, b - 1);
  else
    r = (b - 1) + f(a - 1, b);
  return r;
}

int main()
{
  int a, b;
  scanf("%d%d", &a, &b);
  printf(I64"\n", f(a, b));
  return 0;
}
