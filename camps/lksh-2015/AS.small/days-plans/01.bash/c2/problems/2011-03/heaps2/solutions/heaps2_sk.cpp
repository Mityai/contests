/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2015.04.27
 */

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

const int K = 20;
const int N = 1e6;

int k, m, a[K + 1], f[N + 1];

int main() {
  #define NAME "heaps2"
  assert(freopen(NAME ".in", "r", stdin));
  assert(freopen(NAME ".out", "w", stdout));
  
  scanf("%d", &k);
  forn(i, k)
    scanf("%d", &a[i]);
  sort(a, a + k);
  a[k] = N + 10;
  for (int i = 1; i <= N; i++)
    for (int j = 0; a[j] <= i; j++)
      if (!f[i - a[j]]) {
        f[i] = 1;
        break;
      }
  scanf("%d", &m);
  while (m--) {
    int n;
    scanf("%d", &n);
    puts(f[n] ? "First" : "Second");
  }
  return 0;
}
