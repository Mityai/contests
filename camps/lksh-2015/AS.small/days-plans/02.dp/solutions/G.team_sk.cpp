/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2015.07.07
 */

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define pb push_back
#define sz(a) (int)(a).size()

const int N = 2000;

int n, m, u[N], xn, L, R, e, value[N];
vector<int> c[N], s, x[N];
int f[N + 1][N + 1];

template <class T> inline void relaxMax( T &a, T b ) { a = max(a, b); }

void dfs( int v ) {
  u[v] = 1, s.pb(v);
  for (int x : c[v]) {
    e++;
    if (!u[x])
      dfs(x);
  }
}

int main() {
  #define NAME "team"
  assert(freopen(NAME ".in", "r", stdin));
  assert(freopen(NAME ".out", "w", stdout));
  scanf("%d%d%d%d", &n, &m, &L, &R);
  while (m--) {
    int a, b;
    scanf("%d%d", &a, &b), a--, b--;
    c[a].pb(b), c[b].pb(a);
  }
  forn(i, n) 
    if (!u[i]) {
      s.clear(), e = 0;
      dfs(i);
      value[xn] = e, x[xn++] = s;
    }
  f[0][0] = 1;
  forn(i, xn) {
    copy(f[i], f[i] + n + 1, f[i + 1]);
    forn(w, n + 1)
      if (f[i][w])
        relaxMax(f[i + 1][w + sz(x[i])], f[i][w] + value[i]);
  }
  int ri = L;
  for (int i = L; i <= R; i++)
    if (f[xn][i] > f[xn][ri])
      ri = i;
  if (!f[xn][ri]) {
    puts("-1");
    return 0;
  }
  printf("%d\n", ri);
  while (xn--)
    if (f[xn + 1][ri] != f[xn][ri]) 
      for (int y : x[xn])
        printf("%d ", y + 1), ri--;
  return 0;
}
