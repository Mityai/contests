#define NOFOOTER

#include "testlib.h"

#include <string>
#include <vector>
#include <set>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define mp make_pair

typedef long long ll;
                    
#define CHECK(f, a) { if (!(a)) quitf(f, #a); }
#define ASSERT(a) CHECK(_fail, a)

const int maxQ = (int)1e5;
const int maxN = (int)1e5;
const int maxC = (int)1e9;

int main(int argc, char *argv[])
{
  registerValidation();

  int n, m;
  n = inf.readInt(1, maxN);
  inf.readEoln();
  forn(i, n)
  {
    inf.readInt(0, maxC);
    if (i == n - 1)
      inf.readEoln();
    else
      inf.readSpace();
  }
  m = inf.readInt(1, maxQ);
  inf.readEoln();
  forn(i, m)
  {
    string com = inf.readWord();
    ASSERT(com == "get" || com == "set" || com == "reverse");
    inf.readSpace();
    int L = inf.readInt(1, n);
    inf.readSpace();
    int R = inf.readInt(L, n);
    if (com != "reverse")
    {
      inf.readSpace();
      inf.readInt(0, maxC); 
    }
    inf.readEoln();
  }
  inf.readEof();
  return 0;
}
