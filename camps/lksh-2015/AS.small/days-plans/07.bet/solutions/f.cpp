/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2015.07.13
 */

#include <cstdio>
#include <algorithm>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

const int N = 300010;

int pn, p[N];
int f[N];

int main() {
  int i2 = 0, i3 = 0;
  for (int i = 1;; i++) {
    i2 += i, i3 += i2;
    if (i3 > N)
      break;
    p[pn++] = i3;
  }
  f[0] = 0;
  for (int i = 1; i < N; i++) {
    f[i] = N;
    for (int  j= 0; j < pn && p[j] <= i; j++)
      f[i] = min(f[i], f[i - p[j]] + 1);
  }

  int t, x;
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &x);
    printf("%d\n", f[x]);
  }
  return 0;
}
