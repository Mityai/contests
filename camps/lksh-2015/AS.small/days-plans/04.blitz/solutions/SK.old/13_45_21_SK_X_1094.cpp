/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2012.07.03
 */

#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

#ifdef _WIN32
#  define I64 "%I64d"
#else
#  define I64 "%lld"
#endif

const int maxN = 1010;

char t[maxN];
char s[maxN];
int tn, sn, is[maxN];

int main()
{
  scanf("%s%s", s, t);
  tn = strlen(t);
  sn = strlen(s);
  forn(i, tn - sn + 1)
  {
     is[i] = !strncmp(t + i, s, sn);
//     printf("%d ", is[i]);
  }

  int ma = 0, pos = 0;
  while (pos + sn <= tn)
    if (is[pos])
      ma++, pos += sn;
    else
      pos++;

  int mi = 0;
  pos = 0;
  while (pos + sn <= tn)
    if (is[pos])
    {
      pos += sn - 1;
      while (!is[pos])
        pos--;
      mi++, pos += sn;
    }
    else
      pos++;
  printf("%d %d\n", mi, ma);
  return 0;
}
