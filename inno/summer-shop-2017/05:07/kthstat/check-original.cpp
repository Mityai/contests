
#define NOFOOTER

#include "testlib.h"

#include <sstream>
#include <string>
#include <vector>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long long ll;
                    
#define CHECK(f, a) { if (!(a)) quitf(f, #a); }
#define ASSERT(a) CHECK(_fail, a)

#ifdef _WIN32
#  define I64 "%I64d"
#else
#  define I64 "%Ld"
#endif

string cut( string s )
{
  static const int LEN = 30;
  if ((int)s.length() <= LEN + 10)
    return s;
  return s.substr(0, LEN) + " ...cutted";
}

int main(int argc, char *argv[])
{
  registerTestlibCmd(argc, argv);

  int n = inf.readInt();
  forn(i, n)
    inf.readInt();

  int tn = 0;
  while (!inf.seekEof())
    if (inf.readLine()[0] == '?')
    {
      tn++;
      string cs = ouf.readLine();
      int ca;
      if (sscanf(cs.c_str(), "%d", &ca) != 1)
      {
        stringstream ss(cs);
        string str;
        if ((ss >> str) && str == "SV")
          quitf(_fail, "%d-th line : Securrity Violation = %s", tn, cs.c_str());
        else
          quitf(_pe, "%d-th line : %s is not a number", tn, cut(cs).c_str());
      }
      int ja = ans.readInt();
      if (ca != ja)
        quitf(_wa, "%d-th line : jury (%d) != contestant (%d)", tn, ja, ca);
    }
  ouf.readLine();
  quitf(_ok, "OK (%d)", tn);
  return 0;
}
