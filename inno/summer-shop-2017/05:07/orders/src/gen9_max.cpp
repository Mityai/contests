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
    puts("Usage: <seed for random> <tn>");
    puts("[seed == 0] => Time()");
    return 0;
  }

  int tn = atoi(argv[2]);

  while (tn --> 0)
    printf("1 1\n? 1 1\n");
  puts("0 0");
  return 0;
}
