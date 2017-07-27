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

void gen3()
{
  l = R(1, len);
  r = R(n - len, n);
}

int main( int argc, char *argv[] )
{
  if (argc < 6)
  {
    puts("Usage: <seed for random> <tn> <n> <k> <len>");
    puts("[seed == 0] => Time()");
    return 0;
  }

  int seed = atoi(argv[1]);
  int tn = atoi(argv[2]);
  n = atoi(argv[3]);
  k = atoi(argv[4]);
  c = 1;
  len = atoi(argv[5]);

  initrand(seed ? seed : Time());

  while (tn --> 0)
  {
    int tmp = 10;
    printf("%d %d\n", n, k);
    forn(i, tmp)
    {
      gen2();
      printf("^ %d %d %d\n", l, r, c++);
    }
    forn(i, k - tmp)
    {
      gen3();
      printf("? %d %d\n", l, r);
    }
  }

  puts("0 0");
  return 0;
}
