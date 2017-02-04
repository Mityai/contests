/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2012.07.03
 */

#include <cstdio>
#include <cassert>
#include <algorithm>
#include <map>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

int n, a[130], b[103];
map <int, int> cnt;

int main()
{
  scanf("%d", &n);
  forn(i, n)
  {
    scanf("%d%d", &a[i], &b[i]);
    cnt[a[i]]++;
    cnt[b[i]]++;
  }
  forn(i, n)
    if (cnt[b[i]] & 1)
    {
      printf("%d\n", b[i]);
      return 0;
    }
  return 0;
}
