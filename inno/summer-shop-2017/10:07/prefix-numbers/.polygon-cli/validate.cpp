#include "testlib.h"

int main(int argc, char **argv) {
  registerValidation(argc, argv);
  long long n = inf.readLong();
  ensuref(1 <= n && n <= 1000000000000000000LL, "n is out of bounds [1, 10^18]");
  inf.readEoln();
  inf.readEof();
}
