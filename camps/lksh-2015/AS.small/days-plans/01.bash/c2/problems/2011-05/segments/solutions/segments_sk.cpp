/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2014.10.10
 */

#include <cstdio>
#include <cassert>
#include <algorithm>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef pair <int, int> pii;
#define R first
#define L second

int main() {
  #define NAME "segments"
  assert(freopen(NAME ".in", "r", stdin));
  assert(freopen(NAME ".out", "w", stdout));

  int n;
  scanf("%d", &n);
  pii s[n];
  forn(i, n)
    scanf("%d%d", &s[i].L, &s[i].R);
  sort(s, s + n);

  int L = 0, res = 0;
  forn(i, n)
    if (s[i].L >= L)
      L = s[i].R, res++;
  printf("%d\n", res);
  return 0;
}
