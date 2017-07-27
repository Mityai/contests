#include <cstdio>
#include <cstdlib>
#include <cassert>

#include <algorithm>

#include "random.h"

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

int n, k, c, l, r, len;

void gen1()
{
  l = R(1, n - len);
  r = l + len;
}

void gen2()
{
  l = R(1, n), r = R(1, n);
  if (l > r)
    swap(l, r);
}

int main( int argc, char *argv[] )
{
  if (argc < 7)
  {
    puts("Usage: <seed for random> <tn> <n> <k> <C> <len>");
    puts("[seed == 0] => Time()");
    return 0;
  }

  int seed = atoi(argv[1]);
  int tn = atoi(argv[2]);
  n = atoi(argv[3]);
  k = atoi(argv[4]);
  c = atoi(argv[5]);
  len = atoi(argv[6]);

  initrand(seed ? seed : Time());

  while (tn --> 0)
  {
    printf("%d %d\n", n, 2 * k);
    forn(i, k)
    {
      gen1();
      printf("^ %d %d %d\n", l, r, R(1, c));
      gen2();
      printf("? %d %d\n", l, r);
    }
  }

  puts("0 0");
  return 0;
}
