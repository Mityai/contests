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

ll mul( ll a, ll b, ll c )
{
  ll k = ((long double)a * b + 1) / c;
  ll rest = (a * b + 1) - c * k;
  while (rest < 0) rest += c, k--;
  while (rest >= c) rest -= c, k++;
  return k;
}

ll f( int a, int b )
{
  //printf("%d,%d\n", a, b);
  if (a <= 2)
    return 1;
  if (2 * b > a)
    b = a + 1 - b;
  ll &r = m[mp(a, b)];
  if (r)
    return r;
  if (2 * b == a + 1)
    r = mul(f(a - 1, b - 1), f(a - 1, b), f(a - 2, b - 1));
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
