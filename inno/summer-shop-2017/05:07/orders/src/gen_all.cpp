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
    puts("Usage: <seed for random> <tn> <n> <k> <C>");
    puts("[seed == 0] => Time()");
    return 0;
  }

  int seed = atoi(argv[1]);
  int tn = atoi(argv[2]);
  n = atoi(argv[3]);
  k = atoi(argv[4]);
  c = atoi(argv[5]);

  initrand(seed ? seed : Time());

  while (tn --> 0)
  {
    N = n;//R(n / 2, n);
    C = c;//R(c / 2, c);
    K = k;//R(k / 2, k);

    int l, r;
    printf("%d %d\n", N, K + N * (N + 1) / 2);
    forn(i, K)
    {
      gen(l, r);
      printf("^ %d %d %d\n", l, r, R(1, C));
    }
    forn(i, N)
      forn(j, i + 1)
        printf("? %d %d\n", j + 1, i + 1);
  }
  puts("0 0");
  return 0;
}
