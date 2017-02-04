#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

const double pi = acos(-1);

int main() {
#if __APPLE__
#endif

  int n;
  scanf("%d", &n);

  for (int i = 0; i < n; i++) {
    double l, r;
    cin >> l >> r;

    if (r < l / 2) {
      printf("%.10lf\n", pi * r * r);
    } else if (l * sqrt(2) / 2 < r) {
      printf("%.10lf\n", l * l);
    } else {
      double s = pi * r * r;
      double alpha = 2 * acos(l / 2 / r);
      s -= 2 * r * r * (alpha - sin(alpha));
      printf("%.10lf\n", s);
    }
  }
}
