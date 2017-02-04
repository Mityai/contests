#include <bits/stdc++.h>
using namespace std;

const double pi = acos(-1);

int main() {
  int d, h, v, e;
  cin >> d >> h >> v >> e;

  double r = d * 0.5;
  double s = pi * r * r;

  if (v / s <= e) {
    puts("NO");
  } else {
    puts("YES");
    double t = h / (v / s - e);
    printf("%.10lf\n", t);
  }
}
