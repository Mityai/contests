#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

int main() {
#if __APPLE__
  freopen("C.in", "r", stdin);
  freopen("C.out", "w", stdout);
#endif

  int n;
  double w, v, u;
  scanf("%d%lf%lf%lf", &n, &w, &v, &u);

  if (n <= 2) {
    printf("%.10lf\n", w / u);
    return 0;
  }

  vector< pair<double, double> > pts(n);
  for (int i = 0; i < n; i++) {
    scanf("%lf%lf", &pts[i].fi, &pts[i].se);
  }

  int miny = 0, maxx = 0, minx = 0;
  for (int i = 0; i < n; i++) {
    if (pts[i].se < pts[miny].se) miny = i;
    if (pts[i].fi > pts[maxx].se) maxx = i;
    if (pts[i].fi < pts[minx].se) minx = i;
  }

  double ans = 0;

  bool ok = true;
  for (int i = 0; i < n; i++) {
    double tbus = pts[i].fi / v;
    double tman = pts[i].se / u;
    if (tman > tbus) ok = false;
  }

  if (ok) {
    ans = w / u;
  } else {
    ans = max(pts[miny].se / u, pts[miny].fi / v);
    for (int i = (miny + 1) % n; i != (maxx + 1) % n; i = (i + 1) % n) {
      int prev = (i - 1 + n) % n;
      double nextt = pts[i].fi / v;
      if (nextt <= ans) {
        ans += (pts[i].se - pts[prev].se) / u;
      } else {
        double dist = pts[i].se - pts[prev].se;
        double plustime = dist / u;
        if (ans + plustime < nextt) {
          ans = nextt;
        } else {
          ans += plustime;
        }
      }
    }
    ans += (w - pts[maxx].se) / u;
  }
  printf("%.10lf\n", ans);
}
