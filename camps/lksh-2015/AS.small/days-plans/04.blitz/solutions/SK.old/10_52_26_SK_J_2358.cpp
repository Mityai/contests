/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2012.07.03
 */

#include <cstdio>
#include <cassert>
#include <algorithm>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

int main()
{
 
  int n;
  scanf("%d", &n);
  if (n == 2)
  {
    puts("-1");
    return 0;
  }
  forn(i, n - 1)
    printf("%d ", (i + 1) % (n - 1) + 1);
  printf("%d\n", n);
  return 0;
}
