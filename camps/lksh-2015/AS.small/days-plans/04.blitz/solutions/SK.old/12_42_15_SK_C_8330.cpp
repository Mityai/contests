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

int n, a[103], b[103], del[10003];

void Del( int j )
{
  if (n == 1)
    return;
  for (int k = j + 1; k < n; k++)
    a[k - 1] = a[k], b[k - 1] = b[k];
  n--;
}

int main()
{
  scanf("%d", &n);
  forn(i, n)
    scanf("%d%d", &a[i], &b[i]);
  while (n > 1)
  {
    forn(i, n)
      if (a[i] == b[i] && del[a[i]])
        Del(i), i = n;
    forn(i, n)
      forn(j, n)
        if (i != j && b[i] == a[j])
        {
          del[b[i]] = 1;
          b[i] = b[j];
          Del(j);
          i = j = n;
        }
  }
  printf("%d\n", b[0]);
  return 0;
}
