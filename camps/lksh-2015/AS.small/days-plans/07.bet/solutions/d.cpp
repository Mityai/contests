/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2015.07.13
 */

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long long ll;

int main() {
  int n;
  scanf("%d", &n);
  int x[n], y[n];
  forn(i, n)
    scanf("%d%d", &x[i], &y[i]);
  forn(i, n)
    if ((ll)(x[(i + 1) % n] - x[i]) * (y[(i + 2) % n] - y[i]) - 
        (ll)(x[(i + 2) % n] - x[i]) * (y[(i + 1) % n] - y[i]) >= 0) {
      puts("NO");
      return 0;
    }
  puts("YES");
  return 0;
}
                                                     