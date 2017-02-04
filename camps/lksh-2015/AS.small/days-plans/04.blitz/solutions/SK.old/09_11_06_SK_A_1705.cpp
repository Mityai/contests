/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2012.07.03
 */

#include <cstdio>
#include <cassert>
#include <algorithm>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define fornd(i, n) for (int i = (int)(n) - 1; i >= 0; i--)

int n, cnt[26];
char s[103];

int main()
{
  scanf("%d%s", &n, s);
  forn(i, n)
    cnt[s[i] - 'A']++;
  int odd = 0;
  forn(i, 26)
    if (cnt[i] & 1)
      odd = 'A' + i;
  forn(i, 26)
    forn(j, cnt[i] / 2)
      putchar('A' + i);
  if (odd)
    putchar(odd);
  fornd(i, 26)
    forn(j, cnt[i] / 2)
      putchar('A' + i);
  return 0;
}
