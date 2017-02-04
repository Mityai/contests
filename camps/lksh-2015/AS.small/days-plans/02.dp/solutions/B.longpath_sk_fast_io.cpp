/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2013.03.25
 */

#include <cstdio>
#include <cassert>
#include <algorithm>

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

const int maxn = (int)1e5 + 10;

int e, n, m, d[maxn], next[maxn], head[maxn], to[maxn];

int F( int i )
{
  if (d[i])
    return d[i];
  for (int e = head[i]; e; e = next[e])
    d[i] = std::max(d[i], F(to[e]));
  return ++d[i];
}

inline unsigned int readUInt()
{
  int c = getc(stdin);
  unsigned int x = 0;
  while (c <= 32)
    c = getc(stdin);
  while ('0' <= c && c <= '9')
    x = x * 10 + c - '0', c = getc(stdin);
  return x;
}

int main()
{
  #define NAME "longpath"
  assert(freopen(NAME ".in", "r", stdin));
  assert(freopen(NAME ".out", "w", stdout));

  scanf("%d%d", &n, &m);
  while (m--)
  {
    int a = readUInt() - 1;
    int b = readUInt() - 1;
    next[++e] = head[a], to[e] = b, head[a] = e;
  }

  int res = 0;
  forn(i, n)
    res = std::max(res, F(i));
  printf("%d\n", res - 1);
  return 0;
}
