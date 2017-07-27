/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2014.07.12
 * 0.388 -> 0.300 -> 0.236
 */

#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <algorithm>
#include <vector>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define next next124

const int N = 3e5;
const int E = 3e5;

enum {LOSE = 1, WIN = 2};

int n, m, deg[N], u[N];
int e, head[N], to[E], next[E];

void paint( int v, int ans ) {
  u[v] = ans;
  for (int i = head[v]; i != -1; i = next[i]) {
    int x = to[i];
    if (!u[x]) {
      if (ans == LOSE)
        paint(x, WIN);
      else if (!--deg[x])
        paint(x, LOSE);
    }
  }
}

inline int readUInt()
{
  int c = getchar();
  int x = 0;
  while (c <= 32 && c != -1)
    c = getchar();
  if (c == -1)
    exit(0);
  while ('0' <= c && c <= '9')
    x = x * 10 + c - '0', c = getchar();
  return x;
}

int main() {
  #define NAME "retro"
  assert(freopen(NAME ".in", "r", stdin));
  assert(freopen(NAME ".out", "w", stdout));

  int cnt = 0;
  while (1) {
    n = readUInt();
    m = readUInt();
    if (cnt++)
      puts("");
    assert(1 <= n && n <= N);
    forn(i, n)
      head[i] = -1, deg[i] = 0, u[i] = 0;
    e = 0;
    forn(i, m) {
      int a = readUInt() - 1;
      int b = readUInt() - 1;
      next[e] = head[b], to[e] = a, head[b] = e++;
      deg[a]++;
    }
    forn(i, n)
      if (!deg[i] && !u[i])
        paint(i, LOSE);
    forn(i, n)
      puts(!u[i] ? "DRAW" : (u[i] == LOSE ? "SECOND" : "FIRST"));
  }
  return 0;
}
