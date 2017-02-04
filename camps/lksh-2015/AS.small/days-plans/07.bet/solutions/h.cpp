/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2015.07.13
 */

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

int n, m, c[10][10], u[10], st, ans;

void dfs( int v, int pr, int dep ) {
  if (c[v][st] && dep > 0 && st != pr)
    ans++;
  u[v] = 1;
  for (int i = st + 1; i < n; i++)
    if (!u[i] && i != pr && c[v][i])
      dfs(i, v, dep + 1);
  u[v] = 0;
}

int main() {
  scanf("%d%d", &n, &m);
  while (m--) {
    int a, b;
    scanf("%d%d", &a, &b), a--, b--;
    c[a][b] = c[b][a] = 1;
  }
  forn(i, n)
    st = i, dfs(st, -1, 0);
  cout << ans / 2;
  return 0;
}
