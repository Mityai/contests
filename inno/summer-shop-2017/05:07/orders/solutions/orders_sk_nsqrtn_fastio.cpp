/**
 * Status: OK, 0.313 sec
 *
 * ^ query in O(sqrtN) time
 * ? query in O(sqrtN) time
 */

#include <cstdio>
#include <cstring>
#include <cassert> 
#include <algorithm>

using namespace std; 

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long long ll;

const int S = 200;
const int maxn = (int)1e5;
const int K = maxn / S + 1;

int n, k;
int o[maxn], a[maxn], b[maxn], ma[K], pos[K];
int on1, on2, o1[S], o2[S];
ll bsum[maxn];

inline bool bless( int i, int j )
{
  return a[i] < a[j];
}

void Calc( int j, int x ) // O(S)
{
  int L = j * S, R = L + S;
  if (R > n)
    return;
  on1 = on2 = 0;
  for (int t = L; t < R; t++)
    if (a[o[t]] == x)
      o1[on1++] = o[t];
    else
      o2[on2++] = o[t];
  merge(o1, o1 + on1, o2, o2 + on2, o + L, bless);
  for (int t = L; t < R; t++)
    b[t] = a[o[t]];
  bsum[R - 1] = b[R - 1];
  for (int t = R - 2; t >= L; t--)
    bsum[t] = b[t] + bsum[t + 1];
  pos[j] = upper_bound(b + L, b + R, ma[j]) - b;
}

inline int readInt()
{
  int s = 1, c = getchar();
  int x = 0;
  while (c <= 32)
    c = getchar();
  if (c == '-')
    s = -1, c = getchar();
  while ('0' <= c && c <= '9')
    x = x * 10 + c - '0', c = getchar();
  return x * s;
}

template <class T>
inline void writeInt( T x )
{
  if (x < 0)
    putchar('-'), x = -x;

  char s[24];
  int n = 0;
  while (x || !n)
    s[n++] = '0' + x % 10, x /= 10;
  while (n--)
    putchar(s[n]);
}

int main()
{
  assert(freopen("orders.in", "r", stdin));
  assert(freopen("orders.out", "w", stdout));

  while (1)
  {
    n = readInt();
    k = readInt();
    if (!n && !k)
      return 0;
    forn(i, n)
      o[i] = i, b[i] = a[i] = 0, bsum[i] = 0;
    forn(i, n / S + 1)
      ma[i] = 0;
    for (int i = 0, j = 0; i < n; i += S, j++)
      pos[j] = i;

    forn(i, k)
    {
      char type = getchar();
      int L = readInt() - 1, R = readInt(), x;
      if (type == '^') // 2*Calc + O(S + N/S)
      {
        x = readInt();

        int i = 0, j = 0;
        while (i <= L)
          i += S, j++;
        while (L < R && L < i)
          a[L] = max(a[L], x), L++;
        Calc(j - 1, x);
        while (i + S <= R)
        {
          ma[j] = max(ma[j], x);
          while (pos[j] < i + S && b[pos[j]] <= x)
            pos[j]++;
          i += S, j++;
        }
        while (i < R)
          a[i] = max(a[i], x), i++;
        Calc(j, x);
      }
      else 
      {
        ll cnt = R - L, sum = 0;
        int i = 0, j = 0;
        while (i <= L)
          i += S, j++;
        while (L < R && L < i)
          sum += max(a[L], ma[j - 1]), L++;
        while (i + S <= R)
        {
          int num = pos[j] - i;
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
          writeInt(sum);
        else
          writeInt(sum), putchar('/'), writeInt(cnt);
        putchar('\n');
      }
    }
  }
}
