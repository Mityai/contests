#ifdef BURUNDUK
#  include "my_testlib.h"
#else
#  include "testlib.h"
#endif

#include <string>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define space(i, n) if ((i) == (n) - 1) inf.readEoln(); else inf.readSpace();

const int N = 20;
const int M = 1e4;
const int C = 1e6;

int main(int, char *[]) {
  registerValidation();

  int n = inf.readInt(1, N);
  inf.readEoln();
  forn(i, n) {
    inf.readInt(1, C);
    space(i, n);
  }

  int m = inf.readInt(1, M);
  inf.readEoln();
  forn(i, m) {
    inf.readInt(1, C);
    space(i, m);
  }

  inf.readEof();
  return 0;
}
