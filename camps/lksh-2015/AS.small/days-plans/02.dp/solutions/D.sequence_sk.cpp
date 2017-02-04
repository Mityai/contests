/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2014.11.17
 */

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

int main() {
  #define NAME "sequence"
  assert(freopen(NAME ".in", "r", stdin));
  assert(freopen(NAME ".out", "w", stdout));

  int n, ans = 0;
  cin >> n;
  int a[n], f[n];
  forn(i, n)
    cin >> a[i], f[i] = 0;
  forn(i, n) {
    forn(j, i)
      if (a[i] % a[j] == 0)
        f[i] = max(f[i], f[j]);
    ans = max(ans, ++f[i]);
  }
  printf("%d\n", ans);
  return 0;
}
