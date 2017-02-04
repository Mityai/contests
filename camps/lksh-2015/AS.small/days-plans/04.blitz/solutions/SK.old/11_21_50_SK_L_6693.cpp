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
struct t
{
  double a, b;
};

t p[1003];

bool operator < ( const t &x, const t &y )
{
  #define F(x) (x.a - x.b)
  return F(x) > F(y);
}

int main()
{
  scanf("%d", &n);
  forn(i, n)
    scanf("%lf%lf", &p[i].a, &p[i].b);
  sort(p, p + n);
//  forn(i, n)
//    printf("%lf %lf\n", p[i].a, p[i].b);

  double r = 1e100;
  forn(i, n)
  {
    double s1 = 0, s2 = 0;
    forn(j, n)
      if (j < i)
        s1 += p[j].a;
      else if (j > i)
        s2 += p[j].b;

    double x = 1;
    if (s1 < s2) x -= (s2 - s1) * (1.0 / p[i].a);
    if (s1 > s2) x -= (s1 - s2) * (1.0 / p[i].b);
    x = max(x, 0.0);
    r = min(r, max(s1, s2) + x / (1.0 / p[i].a + 1.0 / p[i].b));
  }
  printf("%.20f\n", r);
  return 0;
}
