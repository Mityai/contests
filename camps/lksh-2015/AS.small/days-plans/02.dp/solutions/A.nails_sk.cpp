/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2014.10.13
 */

#include <cstdio>
#include <cassert>
#include <iostream>
#include <algorithm>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

int main() {
  int n;
  cin >> n;
  int a[n];
  forn(i, n)
    cin >> a[i];
  sort(a, a + n);

  int f[n]; 
  f[0] = 2e9, f[1] = a[1] - a[0];
  for (int i = 2; i < n; i++)
    f[i] = (a[i] - a[i - 1]) + min(f[i - 1], f[i - 2]);
  cout << f[n - 1] << endl;
  return 0;
}
