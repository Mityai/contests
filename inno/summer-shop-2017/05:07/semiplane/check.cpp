#define NOFOOTER

#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define sz(v) (int)(v).size()

typedef long long ll;
                    
#define CHECK(f, a) { if (!(a)) quitf(f, #a); }
#define ASSERT(a) CHECK(_fail, a)

string str( int x )
{
  char buf[99];
  sprintf(buf, "%d", x);
  return string(buf);
}

int main(int argc, char *argv[])
{
  registerTestlibCmd(argc, argv);

  int pos = 0;
  vector <int> v;

  while (!ans.seekEof())
  {
    int a = ouf.readInt();
    int b = ans.readInt();
    pos++;
    if (a != b)
      quitf(_wa, "pos = %d : %d != %d", pos, a, b);

    v.push_back(a);
  }
  if (pos == 0)
  {
    quitf(_ok, "file is empty");
    //quitf(_fail, "file is empty");
  }

  string sv = str(v[0]);
  int M = 3;
  for (int i = 1; i < M && i < sz(v); i++)
    sv += ", " + str(v[i]);
  if (sz(v) > M)
    sv += ", ...";

  quitf(_ok, "OK (n = %d, v = %s)", pos, sv.c_str());
  return 0;
}
