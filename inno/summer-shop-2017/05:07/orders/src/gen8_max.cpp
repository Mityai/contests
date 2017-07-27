#include <cstdio>
#include <cstdlib>
#include <cassert>

#include <algorithm>

#include "random.h"

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

int n, k, c, l, r, len;

void gen4()
{
  l = R(2, n - 1), r = R(2, n - 1);
  if (l > r)
    swap(l, r);
}

int main( int argc, char *argv[] )
{
  if (argc < 5)
  {
    puts("Usage: <seed for random> <tn> <n> <k>");
    puts("[seed == 0] => Time()");
    return 0;
  }

  int seed = atoi(argv[1]);
  int tn = atoi(argv[2]);
  n = atoi(argv[3]);
  k = atoi(argv[4]);
  c = 1;

  initrand(seed ? seed : Time());

  while (tn --> 0)
  {
    printf("%d %d\n", n, 2 * k);
    forn(i, k)
    {
      gen4();
      printf("^ %d %d %d\n", l, r, c++);
      printf("? %d %d\n", l - 1, r + 1);
    }
  }

  puts("0 0");
  return 0;
}
