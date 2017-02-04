/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2014.03.18
 */

#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

const int N = 1000 + 1;

char s[N];
int lcp[N][N];
int n, num_len[N], f[N][N], p[N][N];
int cnt;

inline void relax( int i, int j, int F, int P ) {
  cnt++;
  if (f[i][j] > F)
    f[i][j] = F, p[i][j] = P;
}

void go( int l, int n ) {
  int P = p[l][n];
  if (!P)
    while (n--)
      putchar(s[l++]);
  else if (P > 0)
    go(l, P), go(l + P, n - P);
  else {
    P = -P;
    printf("%d(", n / P);
    go(l, P);
    printf(")");
  }
}

int main()
{
  #define NAME "folding"
  assert(freopen(NAME ".in", "r", stdin));
  assert(freopen(NAME ".out", "w", stdout));

  gets(s);
  assert((n = strlen(s)) < N);
  forn(i, n + 1) {
    char buf[9];
    sprintf(buf, "%d", i);
    num_len[i] = strlen(buf);
  }
  for (int i = n - 1; i >= 0; i--)
    for (int l = 1; i + l < n; l++)
      lcp[i][l] = (s[i] == s[i + l] ? 1 + lcp[i + 1][l] : 0);

  memset(f, 0x10, sizeof(f));
  for (int i = n - 1; i >= 0; i--) {
    for (int r = 1; r <= n - i; r++)
      f[i][r] = r;
    for (int len = 1; len <= n - i; len++)
      for (int k = 2; len * k <= n - i && lcp[i][len] >= len * (k - 1); k++)
        relax(i, len * k, f[i + len][len] + 2 + num_len[k], -len);
    for (int l = 1; l < n - i; l++)
      for (int r = l + 1; r <= n - i; r++)
        relax(i, r, f[i][l] + f[i + l][r - l], l);
  } 
  go(0, n);
  fprintf(stderr, "cnt = %d\n", cnt);
  return 0;
}
