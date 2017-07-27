/**
 * Status: OK, 0.682 sec
 *
 * ^ query in O(sqrtN*logN) time
 * ? query in O(sqrtN*logN) time
 */

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

const int S = 300;
const int maxn = (int)1e5;

int n, k;
int a[maxn], b[maxn], ma[maxn];
ll sum, bsum[maxn];

void Calc( int j, int x )
{
  int L = j * S, R = L + S;
  if (x <= ma[j] || R > n)
    return;
  for (int t = L; t < R; t++)
    b[t] = a[t];
  sort(b + L, b + R);
  bsum[R - 1] = b[R - 1];
  for (int t = R - 2; t >= L; t--)
    bsum[t] = b[t] + bsum[t + 1];
}

int main()
{
  assert(freopen("orders.in", "r", stdin));
  assert(freopen("orders.out", "w", stdout));

  while (scanf("%d%d", &n, &k) == 2 && (n || k))
  {
    memset(a, 0, sizeof(a[0]) * n);
    memset(b, 0, sizeof(b[0]) * n);
    memset(bsum, 0, sizeof(bsum[0]) * n);
    memset(ma, 0, sizeof(ma[0]) * n);

    forn(i, k)
    {
      char type;
      int L, R, x;
      scanf(" %c%d%d", &type, &L, &R), L--;
      if (type == '^')
      {
        scanf("%d", &x);

        int i = 0, j = 0;
        while (i <= L)
          i += S, j++;
        while (L < R && L < i)
          a[L] = max(a[L], x), L++;
        Calc(j - 1, x);
        while (i + S <= R)
          ma[j] = max(ma[j], x), i += S, j++;
        while (i < R)
          a[i] = max(a[i], x), i++;
        Calc(j, x);
      }
      else 
      {
        ll cnt = R - L;
        sum = 0;
        int i = 0, j = 0;
        while (i <= L)
          i += S, j++;
        while (L < R && L < i)
          sum += max(a[L], ma[j - 1]), L++;
        while (i + S <= R)
        {
          int left = i, right = i + S, mid, X = ma[j];
          while (left < right)
            if (b[mid = (left + right) >> 1] < X)
              left = mid + 1;
            else
              right = mid;
          int num = left - i;
          sum += (ll)ma[j] * num;
          if (num < S)
            sum += bsum[i + num];
          i += S, j++;
        }
        while (i < R)
          sum += max(a[i++], ma[j]);

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
