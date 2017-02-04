/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2012.07.03
 */

#include <cstdio>
#include <cassert>
#include <algorithm>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

int n;
double a[1003];
double b[1003];

int main()
{
  scanf("%d", &n);
  forn(i, n)
    scanf("%lf%lf", &a[i], &b[i]);

  double r = 1e100;
  forn(i, n + 1)
  {
    double s = 0;
    forn(j, n)
      s += (j < i ? a[j] : b[j]);
    r = min(r, s);
  }
  printf("%.20f\n", r);
  return 0;
}
