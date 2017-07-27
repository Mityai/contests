#include <set>

using namespace std;

#ifdef BURUNDUK
#  include "my_testlib.h"
#else
#  include "testlib.h"
#endif

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef pair <int, int> pii;

const int maxN = (int)3e5;
const int maxM = (int)3e5;

int main()
{
  registerValidation();

  int sum_n = 0, sum_m = 0;
  while (!inf.eof()) {
    int n = inf.readInt(1, maxN);
    inf.readSpace();
    int m = inf.readInt(1, maxM);
    inf.readEoln();
    sum_n += n, sum_m += m;
    set <pii> s;
    forn(i, m) {
      int a = inf.readInt(1, n);
      inf.readSpace();
      int b = inf.readInt(1, n);
      inf.readEoln();
      //ensure(a != b && s.insert(pii(a, b)).second);
    }
  }
  inf.readEof();
  ensure(sum_n <= maxN && sum_m <= maxM);
  return 0;
}
