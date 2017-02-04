/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2015.07.07
 */

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

const int N = 1000;

char s[N + 1], t[N + 1];
int f[N][N];

int main() {
  #define NAME "palindr"
  assert(freopen(NAME ".in", "r", stdin));
  assert(freopen(NAME ".out", "w", stdout));

  gets(s);
  int n = strlen(s), best = 0, ri, rj;
  for (int i = n - 1; i >= 0; i--)
    for (int j = i; j < n; j++) {
      if (i == j)
        f[i][j] = 1;
      else 
        f[i][j] = max(max(f[i][j - 1], f[i + 1][j]), f[i + 1][j - 1] + 2 * (s[i] == s[j]));
      if (f[i][j] > best)
        best = f[i][j], ri = i, rj = j;
    }
  n = 0;
  while (ri < rj)
    if (f[ri + 1][rj] == f[ri][rj])
      ri++;
    else if (f[ri][rj - 1] == f[ri][rj])
      rj--;
    else
      t[n++] = s[ri++], rj--;
  forn(i, n)
    putchar(t[i]);
  if (ri == rj)
    putchar(s[ri]);
  forn(i, n)
    putchar(t[n - i -1 ]);
  return 0;
}
