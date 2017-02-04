#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

int main() {
#if __APPLE__
  //freopen(".in", "r", stdin);
  //freopen(".out", "w", stdout);
#endif

  double a, b;
  cin >> a >> b;

  int n;
  scanf("%d", &n);

  double ans = 12345678901234567890;
  for (int i = 0; i < n; i++) {
    double x, y, v;
    cin >> x >> y >> v;
    ans = min(ans, sqrt((x - a) * (x - a) + (y - b) * (y - b)) / v);
  }

  printf("%.10lf\n", ans);
}
