/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2012.07.03
 */

#include <cstdio>
#include <cassert>
#include <algorithm>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

const int maxN = (int)1e6 + 10;

int n, p[maxN], z[maxN], s[maxN];
int cc, u[maxN];

int main()
{
  scanf("%d", &n);
  forn(i, n)
    scanf("%d", &p[i]);

  s[0] = 0;
  forn(i, n) if (i)
  {
    if (p[i])
    {
      s[i] = s[p[i] - 1];
      continue;
    }

    cc++;
    int k = p[i - 1];
    while (k && k + 1 != p[i])
    {
      //printf("i = %d : k = %d to %d --> %d\n", i, k, p[k - 1], s[k]);
      u[s[k]] = cc;
      k = p[k - 1];
    }
    if (k + 1 != p[i])
      u[s[0]] = cc;
    
    while (u[s[i]] == cc)
      s[i]++;
  }
/*
  forn(i, n)
    printf("%d ", s[i]);
  puts("");
*/
  
  int l = 0, r = -1;
  z[0] = 0;
  forn(i, n) if (i)
  {
    int k = 0;
    if (r > i)
      k = min(r - i, z[i - l]);
    while (i + k < n && s[k] == s[i + k])
      k++;
    z[i] = k;
    if (i + k > r)
      l = i, r = i + k;
  }
  forn(i, n)
    printf("%d ", z[i]);
  puts("");
  return 0;
}
