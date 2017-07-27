#include <cstdio>
#include <cstdlib>
#include <cassert>

#include <algorithm>

#include "random.h"

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

int n, k, c;
int N, K, C;

void gen( int &l, int &r )
{
  l = R(1, N), r = R(1, N);
  if (l > r)
    swap(l, r);
}

int main( int argc, char *argv[] )
{
  if (argc < 6)
  {
    puts("Usage: <seed for random> <tn> <n> <k> <C> [flag]");
    puts("[seed == 0] => Time()");
    return 0;
  }

  int seed = atoi(argv[1]);
  int tn = atoi(argv[2]);
  n = atoi(argv[3]);
  k = atoi(argv[4]);
  c = atoi(argv[5]);
  int flag = argc >= 7 ? atoi(argv[6]) : 0;

  initrand(seed ? seed : Time());

  while (tn --> 0)
  {
    N = R(n / 2, n);
    C = R(c / 2, c);
    K = R(k / 2, k);
    if (flag)
      N = n, C = c, K = k;

    int l, r;
    printf("%d %d\n", N, 2 * K);
    forn(i, K)
    {
      gen(l, r);
      printf("^ %d %d %d\n", l, r, R(1, C));
      gen(l, r);
      printf("? %d %d\n", l, r);
    }
  }
  puts("0 0");
  return 0;
}
