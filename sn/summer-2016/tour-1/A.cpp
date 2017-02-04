#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

const double pi = acos(-1);

int main() {
  double n;
  double r;
  cin >> n >> r;

  double R = r / cos(pi / n);
  for (int i = 0; i < n; i++) {
    printf("%.10lf %.10lf\n", R * cos(2 * pi * i / n), R * sin(2 * pi * i / n));
  }
}
