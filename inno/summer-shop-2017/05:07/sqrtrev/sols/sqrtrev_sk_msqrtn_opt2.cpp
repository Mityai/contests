/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2012.02.24
 */

/* Template */

#include <cstdarg>
#include <ctime>
#include <cmath>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>

#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <functional>
#include <map>
#include <set>
#include <fstream>
#include <queue>
#include <bitset>
#include <numeric>
#include <iterator>

using namespace std;

#ifdef _WIN32
#  define I64 "%I64d"
#else
#  define I64 "%Ld"
#endif

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define fornd(i, n) for (int i = (int)(n) - 1; i >= 0; i--)
#define forab(i, a, b) for (int i = (int)(a); i <= (int)(b); i++)
#define forabd(i, a, b) for (int i = (int)(b); i >= (int)(a); i--)
#define forit(i, a) for (__typeof((a).begin()) i = (a).begin(); i != (a).end(); i++)
#define sz(a) (int)(a).size()
#define all(a) (a).begin(), (a).end()
#define zero(a) memset(a, 0, sizeof(a))
#define Fill(a, x) memset(a, x, sizeof(a))
#define pb push_back
#define mp make_pair
#define uni(a) (unique(all(a)) - (a).begin());
#define BS(a, x, less) (lower_bound(all(a), x, less) - (a).begin())

#define EOL(i, n) " \n"[i == (n) - 1]
#define LEN(a) (int)(sizeof(a) / sizeof(a[0]))
#define IS(a, i) (((a) >> (i)) & 1)
#define LAST(a) a[sz(a) - 1]
#define ONE(n) ((1 << (n)) - 1)

typedef short int16;
typedef unsigned short uint16;
typedef unsigned int uint;
typedef double dbl;
typedef long long ll;
typedef unsigned long long ull;
typedef vector <int> vi;
typedef vector <vi> vvi;
typedef vector <string> vs;
typedef pair <int, int> pii;
typedef vector <pii> vpii;
typedef unsigned char byte;

template <class T> T inline sqr(T x) { return x * x; }
template <class T> inline void relaxMin( T &a, T b ) { a = min(a, b); }
template <class T> inline void relaxMax( T &a, T b ) { a = max(a, b); }
template <class T> inline T sign( T x ) { return x > 0 ? 1 : (x < 0 ? -1 : 0); }
template <class T> inline T myAbs( T a ) { return a > 0 ? a : -a; }
template <class T> T iteratorK( T a, int k ) { while (k--) a++; return a; }

void err( const char *fmt, ... )
{
  //#if DEBUG
  va_list list;
  va_start(list, fmt);
  vfprintf(stderr, fmt, list);
  fflush(stderr);
  //#endif
}

void Assert( bool f, const char *fmt = "", ... )
{
  if (!f)
  {
    va_list list;
    va_start(list, fmt);
    err(fmt, list);
    exit(1);
  }
}

unsigned R() { return (rand() << 15) + rand(); }

/* String converter */

template <class T> string str( T i );
template <class P1, class P2> string str( pair <P1, P2> i );
template <class T> string str( T begin, T end );
template <class T> string str( vector <T> i ) { return str(all(i)); }
template <class T> string str( int n, T begin ) { return str(begin, begin + n); }
string str( int i ) { char s[100]; sprintf(s, "%d", i); return string(s); }

template <class T> string str( T i )
{ 
  stringstream ss;
  ss << i;
  return ss.str();
}
template <class P1, class P2> string str( pair <P1, P2> i )
{ 
  stringstream ss;
  ss << "<" << str(i.first) << ", " << str(i.second) << ">";
  return ss.str();
}
template <class T> string str( T begin, T end )
{
  stringstream ss;
  ss << "[";
  int f = 0;
  while (begin != end)
    ss << (f ? ", " : "") << str(*begin++), f = 1;
  ss << "]";
  return ss.str();
}
string str( ll num, int bn )
{
  stringstream ss;
  while (bn--)
    ss << (num & 1), num >>= 1;
  return ss.str();
}
string str( int num, int bn ) { return str((ll)num, bn); }
#define cstr(...) str(__VA_ARGS__).c_str()
/* The main part */

#define NAME "sqrtrev"

const int maxN = (int)1e5;
const int SIZE = 1200;

int mem[2][maxN];
int sn, n, m, *a = mem[0], *b = mem[1];

struct Seg
{
  int st, len, rev, set;

  Seg() { }
  Seg( int _st, int _len, int _rev, int _set ) : st(_st), len(_len), rev(_rev), set(_set) { }

  inline int get( int x )
  {
    if (set != -1)
      return set >= x ? len : 0;
    return (b + st + len) - lower_bound(b + st, b + st + len, x);
  }
};

Seg s[SIZE + 3];

void Init()
{
  forn(i, n)
    b[i] = a[i];
  sn = 0;
  int pos = 0, x = n / (SIZE / 4) + 1;
  while (pos < n)
  {
    int p = min(pos + x, n);
    s[sn++] = Seg(pos, p - pos, 0, -1);
    sort(b + pos, b + p);
    pos = p;
  }
  s[sn].len = 1;
}

int Split( int x )
{
  int pos = 0, i = 0;
  while (pos + s[i].len <= x)
    pos += s[i++].len;
  if (pos != x)
  {
    memmove(s + i + 2, s + i + 1, sizeof(Seg) * (sn - i - 1));
    sn++;

    int k = x - pos;
    s[i + 1].set = s[i].set;
    s[i + 1].len = s[i].len - k;
    s[i].len = k;
    if (s[i].rev)
    {
      s[i + 1].rev = 1;
      s[i + 1].st = s[i].st;
      s[i].st += s[i + 1].len;
    }
    else
    {
      s[i + 1].rev = 0;
      s[i + 1].st = s[i].st + k;
    }
    forn(t, 2)
    {
      memcpy(b + s[i + t].st, a + s[i + t].st, s[i + t].len * sizeof(a[0]));
      sort(b + s[i + t].st, b + s[i + t].st + s[i + t].len);
    }
    s[sn].len = 1;
    i++;
  }
  return i;
}

int calc( int set, int l, int len, int x )
{
  if (set != -1)
    return set >= x ? len : 0;

  int cnt = 0, r = l + len;
  while (l < r)
    cnt += (a[l++] >= x);
  return cnt;
}

int main()
{
#ifdef DEBUG
  double tmp_start = clock();
  fprintf(stderr, "Start\n");
#endif

  assert(freopen(NAME ".in", "r", stdin));
  assert(freopen(NAME ".out", "w", stdout));

  scanf("%d", &n);
  forn(i, n)
    scanf("%d", &a[i]);
  Init();

  scanf("%d", &m);
  while (m--)
  {
    char com[9];
    int l, r, x;
    scanf("%s%d%d", com, &l, &r), l--;
    if (!strcmp(com, "get"))
    {
      int cnt = 0;
      scanf("%d", &x);

      int pos = 0, i = 0;
      while (pos + s[i].len <= l)
        pos += s[i++].len;
      if (i < sn && pos < l)
      {
        if (pos + s[i].len >= r)
        {
          if (s[i].rev)
            cnt += calc(s[i].set, s[i].st + s[i].len - (l - pos) - (r - l), r - l, x);
          else
            cnt += calc(s[i].set, s[i].st + (l - pos), r - l, x);
        }
        else
        {
          int k = s[i].len - (l - pos);
          if (s[i].rev)
            cnt += calc(s[i].set, s[i].st + s[i].len - (l - pos) - k, k, x);
          else
            cnt += calc(s[i].set, s[i].st + (l - pos), k, x);
        }
        pos += s[i++].len;
      }
      while (i < sn && pos + s[i].len <= r)
        pos += s[i].len, cnt += s[i++].get(x);
      if (i < sn && pos < r)
      {
        int k = r - pos;
        if (s[i].rev)
          cnt += calc(s[i].set, s[i].st + s[i].len - k, k, x);
        else
          cnt += calc(s[i].set, s[i].st, k, x);
      }
      printf("%d\n", cnt);
    }
    else if (!strcmp(com, "set"))
    {
      l = Split(l), r = Split(r);
      scanf("%d", &x);
      while (l < r)
        s[l++].set = x;
    }
    else // reverse
    {
      l = Split(l), r = Split(r);
      reverse(s + l, s + r);
      while (l < r)
        s[l++].rev ^= 1;
    }     

    if (sn >= SIZE)
    {
      n = 0;
      forn(i, sn)
        if (s[i].set != -1)
        {
          int x = s[i].set, m = s[i].len;
          while (m--)
            b[n++] = x;
        }
        else
        {
          int pos = n, *A = a + s[i].st, m = s[i].len;
          while (m--)
            b[n++] = *A++;
          if (s[i].rev)
            reverse(b + pos, b + n);
        }
      swap(a, b);
      Init();
    }
  }

#ifdef DEBUG
  fprintf(stderr, "Total time = %.2lf\n", (clock() - tmp_start) / CLOCKS_PER_SEC);
#endif
  return 0;
}
