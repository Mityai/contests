/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2014.02.18
 */

#include <cstdio>
#include <cstdlib>

#include "random.h"

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

int main( int argc, char *argv[] )
{
  if (argc < 6)
  {
    puts("Usage: <seed for random> <n> <m1> <m2> <tn>");
    puts("  [seed == 0] => Time()");
    puts("  n - number of vertices");
    puts("  [m1..m2] - number of edges");
    puts("  tn - number of testsets");
    return 1;
  }

  int seed = atoi(argv[1]);
  int n = atoi(argv[2]);
  int m1 = atoi(argv[3]);
  int m2 = atoi(argv[4]);
  int tn = atoi(argv[5]);

  if (seed == 0)
    seed = Time(), fprintf(stderr, "seed = %d\n", seed);
  initrand(seed);

  while (tn--) {
    int m = R(m1, m2);
    printf("%d %d\n", n, m);
    forn(i, m)
      printf("%d %d\n", R(1, n), R(1, n));
  }
  return 0;
}
