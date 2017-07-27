#define NOFOOTER

#include "testlib.h"

#include <cstring>
#include <string>
#include <vector>
#include <set>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define mp make_pair

typedef long long ll;
                    
#define CHECK(f, a) { if (!(a)) quitf(f, #a); }
#define ASSERT(a) CHECK(_fail, a)

const int MAX = (int)1e4;
const int maxN = (int)5e4;

int main(int argc, char *argv[])
{
  registerValidation();

  int n = inf.readInt(1, maxN);
  inf.readSpace();
  int m = inf.readInt(1, maxN);
  inf.readSpace();
  int C = inf.readInt(1, MAX);
  inf.readEoln();
  forn(i, n)
  {
    inf.readInt(0, C);
    inf.readSpace();
    inf.readInt(0, C);
    inf.readEoln();
  }
  forn(i, m)
  {
    int a = inf.readInt(-MAX, MAX);
    inf.readSpace();
    int b = inf.readInt(-MAX, MAX);
    ASSERT(a != 0 || b != 0);
    inf.readSpace();
    inf.readInt(-MAX, MAX);
    inf.readEoln();
  }
  inf.readEof();
  return 0;
}
