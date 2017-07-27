#include <cstdio>
#include <cstdlib>
#include <cassert>

#include <algorithm>

#include "random.h"

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

int main( int argc, char *argv[] )
{
  if (argc < 3)
  {
    puts("Usage: <seed for random> <n>");
    puts("[seed == 0] => Time()");
    return 0;
  }

  int seed = atoi(argv[1]);
  int n = atoi(argv[2]);

  initrand(seed ? seed : Time());

  printf("%d %d\n", n, n);
  forn(i, n)
    printf("^ %d %d %d\n", n, n, (int)1e9);
  puts("0 0");
  return 0;
}
