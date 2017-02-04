/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2015.04.19
 */

#include <bits/stdc++.h>

using namespace std;

int greedy(int x, int a, int y, int b, int l) {
  int *h = new int[l]();
  if (a < b)
    swap(a, b), swap(x, y);
  while (x--) *min_element(h, h + l) += a;
  while (y--) *min_element(h, h + l) += b;
  return *min_element(h, h + l);
}

void relax( int &a, int b ) {
  a = min(a, b);
}

int main() {
  assert(freopen("bridge.in", "r", stdin));
  assert(freopen("bridge.out", "w", stdout));

  int a, b, l, x, y;
  while (scanf("%d%d%d%d%d", &x, &a, &y, &b, &l) == 5) {
    if (a < b)
      swap(a, b), swap(x, y);
    int maxw = (x * a + y * b) / l, minw = greedy(x, a, y, b, l);
    int d[2][x + 1];
    while (minw < maxw) {
      int good = 0, ave = (minw + maxw + 1) / 2;
      int X = (ave + a - 1) / a, dy[X + 1];
      for (int k = 0; k <= X; k++)
        dy[k] = max(0, ave - k * a + b - 1) / b;
      memset(d, 0x10, sizeof(d));
      d[0][0] = 0;
      for (int i = 0, run = 1; run && i <= l; i++) {
        run = 0;
        memset(d[(i + 1) & 1], 0x10, sizeof(d[0]));
        for (int j = 0; j <= x; j++) 
          if (d[i & 1][j] <= y) {
            run = 1;
            if (i == l) 
              good = 1;
            else
              for (int k = 0; k + j <= x && k <= X; k++) 
                relax(d[(i + 1) & 1][k + j], d[i & 1][j] + dy[k]);
          }
      }
      if (good)
        minw = ave;
      else
        maxw = ave - 1;
    }
    printf("%d\n", minw);
  }
  return 0;
}
