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

const int maxN = (int)1e4 + 1;
const int maxQ = (int)1e6;

char d[maxN + 11][maxN + 111];
int rn, r[maxN];
int qst, qen, qs[maxQ], qp[maxQ];

inline void add( int s, int p, int dd )
{
  if (s > maxN || p > maxN || d[s][p])
    return;
  d[s][p] = dd;
  qs[qen] = s;
  qp[qen++] = p;
  if (qen == maxQ) qen = 0;
}

int main()
{
  add(0, 0, 1);
  while (qst < qen)
  {
    int s = qs[qst];
    int p = qp[qst++];
    if (qst == maxQ) qst = 0;
    for (int d = 1; d <= 9; d++)
      add(s + d, p + d * d, d);
  }

  int T;
  scanf("%d", &T);
  while (T--)
  {
    int s, p;
    scanf("%d%d", &s, &p);
    if (!d[s][p])
    {
      puts("No solution");
      continue;
    }
    rn = 0;
    while (s > 0)
    {
      int dd = d[s][p];
      s -= dd, p -= dd * dd;
      r[rn++] = dd;
    }
    while (rn-- > 0)
      putchar(r[rn] + '0');
    puts("");
  }
  return 0;
}
