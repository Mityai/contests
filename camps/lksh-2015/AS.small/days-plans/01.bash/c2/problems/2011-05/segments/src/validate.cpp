#define NOFOOTER

#ifdef BURUNDUK
#  include "my_testlib.h"
#else
#  include "testlib.h"
#endif

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

const int N = (int)1e5;
const int M = (int)1e9;

int main(int, char *[])
{
  registerValidation();

  int n = inf.readInt(1, N);
  inf.readEoln();
  forn(i, n)
  {
    int l = inf.readInt(1, M);
    inf.readSpace();
    inf.readInt(l + 1, M);
    inf.readEoln();
  }
  inf.readEof();
  return 0;
}
