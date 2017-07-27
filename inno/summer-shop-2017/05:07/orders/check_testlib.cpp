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

int tn;
double sn, sq;

void readInput()
{
  while (1)
  {
    int n = inf.readInt();
    int q = inf.readInt();
    if (!n && !q)
      break;
    tn++, sn += n, sq += q;
    while (q--)
    {
      string t = inf.readWord();
      inf.readInt();
      inf.readInt();
      if (t == "^")
        inf.readInt();
    }
  }
}

int main(int argc, char *argv[])
{
  registerTestlibCmd(argc, argv);

  readInput();

  int pos = 0;
  vector <string> v;

  while (!ans.seekEof())
  {
    string a = ouf.readWord();
    string b = ans.readWord();
    pos++;
    if (a != b)
      quitf(_wa, "pos = %d : %s != %s", pos, a.c_str(), b.c_str());
    v.push_back(a);
  }

  string sv = "<empty>";
  if (sz(v))
  {
    sv = v[0];
    int M = 3;
    for (int i = 1; i < M && i < sz(v); i++)
      sv += ", " + v[i];
    if (sz(v) > M)
      sv += ", ...";
  }
  quitf(_ok, "OK (%d tests, average n = %.2f, average q = %.2f, answers = %s)", tn, sn / tn, sq / tn, sv.c_str());
  return 0;
}
