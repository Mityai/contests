#include "testlib.h"

#include <string>

using namespace std;

const int MAX_SUMN = (int)1e5,
          MAX_SUMK = (int)1e5,
          MAX_X = (int)1e9;

int main() {
  registerValidation();
  int sumk1 = 0, sumk2 = 0, sumn = 0;

  while (true) {
    int n = inf.readInt();
    inf.readSpace();
    int k = inf.readInt();
    inf.readEoln();

    if (n == 0 && k == 0)
      break;
    ensure(n >= 0 && k >= 0);
    sumn += n;

    for (int o = 0; o < k; o++) {
      string t = inf.readWord("[?^]");
      ensure(t.length() == 1);
      inf.readSpace();
      if (t == "^") {
        int L = inf.readInt(1, n);
        inf.readSpace();
        inf.readInt(L, n);
        inf.readSpace();
        inf.readInt(1, MAX_X);
        sumk1++;
      }
      else if (t == "?") {
        int L = inf.readInt(1, n);
        inf.readSpace();
        inf.readInt(L, n);
        sumk2++;
      }
      else
        quitf(_fail, "Unknown type of query: '%s'", t.c_str());
      inf.readEoln();
    }
  }
  inf.readEof();
  ensure(sumn <= MAX_SUMN);
  ensure(sumk1 + sumk2 <= MAX_SUMK);
  return 0;
}
