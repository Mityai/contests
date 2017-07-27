/**
 * Status: TL 19, >3 sec
 *
 * ^ query in O(logN) time
 * ? query in O(N) time
 */

#include <cassert> 
#include <cstdio>
#include <cstring>
#include <cassert> 
#include <algorithm>

using namespace std; 

#ifdef _WIN32
#  define I64 "%I64d"
#else
#  define I64 "%Ld"
#endif

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long long ll;

const int maxn = 1 << 17;

int n, k, L, R, x;
int val[maxn * 2];
ll sum;

void add( int v, int vL, int vR )
{
  assert(1 <= v && v < maxn * 2);

  if (vL > R || L > vR)
    return;
  if (L <= vL && vR <= R)
  {
    val[v] = max(val[v], x);
    return;
  }

  int vM = (vL + vR) >> 1;
  add(2 * v, vL, vM);
  add(2 * v + 1, vM + 1, vR);
}

void get( int v, int vL, int vR, int x )
{
  assert(1 <= v && v < maxn * 2);

  if (vL > R || L > vR)
    return;

  x = max(x, val[v]);
  if (vL == vR)
  {
    sum += x;
    return;
  }    

  int vM = (vL + vR) >> 1;
  get(2 * v, vL, vM, x);
  get(2 * v + 1, vM + 1, vR, x);
}

int main()
{
  assert(freopen("orders.in", "r", stdin));
  assert(freopen("orders.out", "w", stdout));

  while (scanf("%d%d", &n, &k) == 2 && (n || k))
  {
    int ma = 1;
    while (ma <= n)
      ma *= 2;
    assert(ma <= maxn);
    memset(val, 0, sizeof(val[0]) * (ma * 2));

    forn(i, k)
    {
      char type;
      scanf(" %c%d%d", &type, &L, &R), L--, R--;
      if (type == '^')
      {
        scanf("%d", &x);
        add(1, 0, n - 1);
      }
      else 
      {
        ll cnt = R - L + 1;
        sum = 0;
        get(1, 0, n - 1, 0);

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
