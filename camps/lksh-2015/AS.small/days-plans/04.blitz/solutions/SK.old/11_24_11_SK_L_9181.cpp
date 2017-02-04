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
  #define F(x) (1.0 / x.a - 1.0 / x.b)
  return F(x) < F(y);
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

    double x = 1, va = (1.0 / p[i].a), vb = (1.0 / p[i].b);
    if (s1 < s2) x -= (s2 - s1) * va;
    if (s1 > s2) x -= (s1 - s2) * vb;
    x = max(x, 0.0);
    r = min(r, max(s1, s2) + x / (va + vb));
  }
  printf("%.20f\n", r);
  return 0;
}
