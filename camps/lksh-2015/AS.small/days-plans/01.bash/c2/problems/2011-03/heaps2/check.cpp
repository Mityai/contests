/**
 * Standard checker: compare two vectors of words
 */

#define NOFOOTER

#ifdef BURUNDUK
#  include "my_testlib.h"
#else
#  include "testlib.h"
#endif

#include <string>
#include <vector>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define sz(v) (int)(v).size()

string myPart( string s )
{
  static const int LEN = 30;
  if ((int)s.length() <= LEN + 10)
    return s;
  return s.substr(0, LEN) + " ...cutted";
}

int main(int argc, char *argv[])
{
  registerTestlibCmd(argc, argv);

  int pos = 0;
  vector <string> v;

  while (!ans.seekEof())
  {
    string a = ouf.readWord();
    string b = ans.readWord();
    pos++;
    if (a != b)
      quitf(_wa, "pos = %d : contestant(%s) != jury(%s)", pos, myPart(a).c_str(), myPart(b).c_str());

    v.push_back(a);
  }
  if (pos == 0)
    quitf(_ok, "file is empty");

  string sv = myPart(v[0]);
  int M = 3;
  for (int i = 1; i < M && i < sz(v); i++)
    sv += ", " + myPart(v[i]);
  if (sz(v) > M)
    sv += ", ...";

  quitf(_ok, "OK (n = %d, v = %s)", pos, sv.c_str());
  return 0;
}
