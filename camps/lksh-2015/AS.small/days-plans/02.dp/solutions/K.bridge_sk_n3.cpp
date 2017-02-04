/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2015.04.14
 */

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define fill(a, x) memset(a, x, sizeof(a))

const int N = 151;

int f[N][N][N];
int a, b, cnt;

int go( int x, int y, int l ) {
  int &r = f[x][y][l];
  if (r != -1)
    return r;
  cnt++;
  if (l == 1)
    return r = a * x + y * b;
  r = 0;
  if (y >= l)
    r = max(r, go(x, y - l, l) + b);
  int ma = (a * x + b * y) / l, k = ma / a;
  if (x >= k && k) 
    r = max(r, min(k * a, go(x - k, y, l - 1)));
  if (x >= k + 1) 
    r = max(r, go(x - k - 1, y, l - 1));
  return r;
}

int main() {
  #define NAME "bridge"
  assert(freopen(NAME ".in", "r", stdin));
  assert(freopen(NAME ".out", "w", stdout));

  int x, y, l;
  fill(f, -1);
  cin >> x >> a >> y >> b >> l;
  if (a < b)
    swap(a, b), swap(x, y);
  cout << go(x, y, l) << endl;
  fprintf(stderr, "cnt = %d [l=%d]\n", cnt, l);
  return 0;
}
