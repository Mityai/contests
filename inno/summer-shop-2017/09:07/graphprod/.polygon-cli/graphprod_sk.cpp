#include <cstring>
#include <cstdio>
#include <cassert>

#include <algorithm>
#include <vector>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define pb push_back

const int maxn = (int)1e5;

vector <int> c[maxn];
int n, m, a, b, d[2][maxn], *d1;

int dfs( int v )
{
  if (d1[v] != -1)
    return d1[v];
  d1[v] = 0;
  forn(i, c[v].size())
  {
    int x = dfs(c[v][i]);
    if (((d1[v] & 1) && !(x & 1) && d1[v] > x + 1) ||
        (!(d1[v] & 1) && (!(x & 1) || ((x & 1) && (d1[v] < x + 1)))))
      d1[v] = x + 1;
  }
  return d1[v];
}

int main()
{

  memset(d, -1, sizeof(d));
  forn(t, 2)
  {
    scanf("%d%d", &n, &m);
    forn(i, n)
      c[i].clear();
    while (m--)
    {
      scanf("%d%d", &a, &b), a--, b--;
      c[a].pb(b);
    }
    d1 = d[t];
    forn(i, n)
      dfs(i);
  }
  scanf("%d", &n);
  while (n--)
  {
    scanf("%d%d", &a, &b), a--, b--;
    puts((min(d[0][a], d[1][b]) & 1) ? "first" : "second");
  }
  return 0;
}
