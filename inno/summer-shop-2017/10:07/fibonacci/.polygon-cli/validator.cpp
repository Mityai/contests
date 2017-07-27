#include "testlib.h"

int main(int argc, char ** argv) {
  registerValidation();
  int k = inf.readInt(2, 10);
  inf.readSpace();
  int n = inf.readLong(0, 1000000000000000000LL);
  inf.readEoln();
  for (int i = 0; i < k; i++) {
     inf.readInt(0, 1000000000);
     if (i + 1 < k)
        inf.readSpace();
  }
  inf.readEoln();
  for (int i = 0; i < k; i++) {
     inf.readInt(0, 1000000000);
     if (i + 1 < k)
         inf.readSpace();
  }
  inf.readEoln();
  inf.readEof();
}
