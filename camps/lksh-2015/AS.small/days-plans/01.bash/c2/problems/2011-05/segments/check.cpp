/**
 * Standard checker: compare two 32-bit signed integers
 */

#define NOFOOTER

#ifdef BURUNDUK
#  include "my_testlib.h"
#else
#  include "testlib.h"
#endif

int main(int argc, char *argv[])
{
  registerTestlibCmd(argc, argv);

  int a = ouf.readInt();
  int b = ans.readInt();

  if (a != b)
    quitf(_wa, "contestant(%d) != jury(%d)", a, b);
  quitf(_ok, "OK (%d)", a);
  return 0;
}
