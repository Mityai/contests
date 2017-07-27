/**
 * Status: TL 19, >3 sec
 *
 * ^ query in O(N) time
 * ? query in O(N) time
 */

#include <cassert> 
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std; 

#ifdef _WIN32
#  define I64 "%I64d"
#else
#  define I64 "%Ld"
#endif

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long long ll;

const int maxn = (int)1e5;

int n, k, val[maxn];

int main()
{
  assert(freopen("orders.in", "r", stdin));
  assert(freopen("orders.out", "w", stdout));

  while (scanf("%d%d", &n, &k) == 2 && (n || k))
  {
    memset(val, 0, sizeof(val[0]) * n);
    forn(i, k)
    {
      char type;
      int L, R, x;

      scanf(" %c%d%d", &type, &L, &R), L--, R--;
      if (type == '^')
      {
        scanf("%d", &x);
        while (L <= R)
          val[L] = max(val[L], x), L++;
      }
      else 
      {
        ll sum = 0, cnt = R - L + 1;
        while (L <= R)
          sum += val[L++];

        ll g = __gcd(sum, cnt);
        sum /= g, cnt /= g;
        if (cnt == 1)
          printf(I64"\n", sum);
        else
          printf(I64"/"I64"\n", sum, cnt);
      }
    }
  }
  return 0;
}
