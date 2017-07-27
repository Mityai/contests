/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2014.07.12
 */

#include <cstdio>
#include <cassert>
#include <algorithm>
#include <vector>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

const int N = 3e5;

enum {LOSE = 1, WIN = 2};

int n, m, deg[N], u[N];
vector <int> rc[N];

void paint( int v, int ans ) {
  u[v] = ans;
  forn(i, rc[v].size()) {
    int x = rc[v][i];
    if (!u[x]) {
      if (ans == LOSE)
        paint(x, WIN);
      else if (!--deg[x])
        paint(x, LOSE);
    }
  }
}

int main() {
  #define NAME "retro"
  assert(freopen(NAME ".in", "r", stdin));
  assert(freopen(NAME ".out", "w", stdout));

  int cnt = 0;
  while (scanf("%d%d", &n, &m) == 2) {
    if (cnt++)
      puts("");
    assert(1 <= n && n <= N);
    forn(i, n)
      rc[i].clear(), deg[i] = 0, u[i] = 0;
    forn(i, m) {
      int a, b;
      scanf("%d%d", &a, &b), a--, b--;
      rc[b].push_back(a);
      deg[a]++;
    }
    forn(i, n)
      if (!deg[i] && !u[i])
        paint(i, LOSE);
    forn(i, n)
      printf("%s\n", !u[i] ? "DRAW" : (u[i] == LOSE ? "SECOND" : "FIRST"));
  }
  return 0;
}
