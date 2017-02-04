/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2015.07.13
 */

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define mp make_pair

const int N = 1e6;

int n;
struct Pnt {
  int x, y, i;
  bool operator < ( Pnt p ) const { return mp(-x, -y) < mp(-p.x, -p.y); }
} p[N];

int main() {
  scanf("%d", &n);
  forn(i, n)
    scanf("%d%d", &p[i].x, &p[i].y), p[i].i = i;
  sort(p, p + n);

  int an = 0, a[N], ma = INT_MIN;
  forn(i, n) 
    if (!i || p[i].y > ma) 
      a[an++] = p[i].i, ma = p[i].y;
  printf("%d\n", an);
  forn(i, an)
    printf("%d ", a[i] + 1);
  return 0;
}
