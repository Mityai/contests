#include <cstdio>
#include <cstdlib>
#include <cassert>

#include <algorithm>

#include "random.h"

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

#define EOL(i, n) " \n"[i == (n) - 1]

int main( int argc, char *argv[] )
{
  if (argc < 5)
  {
    puts("Usage: <seed for random> <n> <k> <M>");
    puts("[seed == 0] => Time()");
    return 0;
  }

  int seed = atoi(argv[1]);
  int n = atoi(argv[2]);
  int k = atoi(argv[3]);
  int M = atoi(argv[4]);

  initrand(seed ? seed : Time());

  printf("%d\n", n);
  forn(i, n)
    printf("%d%c", R(0, M), EOL(i, n));
  forn(i, k)
  {
    if (n >= 1 && R(0, 1))
    {
      int l = R(1, n), r = R(1, n);
      printf("? %d %d %d\n", 0, n-1, R(0, M));
    }
    else
    {
      if (n >= 1 && R(0, 1))
        printf("- %d\n", R(0, n - 1)), n--;
      else
        printf("+ %d %d\n", R(0, n), R(0, M)), n++;
    }
  }
  return 0;
}
