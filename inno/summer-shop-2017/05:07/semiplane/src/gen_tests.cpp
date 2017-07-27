#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <cstdarg>
#include <cmath>

#include <algorithm>
#include <iostream>
#include <set>

#include "random.h"

using namespace std;

#define TMP_FILE "tmp.tmp"

#ifdef _WIN32
#  define PREFIX ""
#  define DEL_COMMAND "del"
#  define I64 "%I64d"
#else
#  define PREFIX "./"
#  define DEL_COMMAND "rm"
#  define I64 "%Ld"
#endif

#define GET_ARG(msg, s) \
{ \
  va_list list;  \
  va_start(list, msg); \
  vsprintf(s, msg, list); \
}

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define forab(i, a, b) for (int i = (int)(a); i <= (int)(b); i++)
#define mp make_pair

#define LEN(a) (int)(sizeof(a) / sizeof(a[0]))

typedef long long ll;

/**
 * Do not change this part 
 */

#define RAND_SEED ((int)1e9 + 7)

const int maxLen = (int)1e4 + 10;

static int cnt = 0;

void ReadFile( const char *fileName ); // Reads all tests from file

void ASSERT( bool f, const char *msg, ... )
{
  if (!f)
  {
    va_list ap;
    va_start(ap, msg);
    vfprintf(stderr, msg, ap);
    exit(1);
  }
}

void NewTest()
{
  char buf[99];

  cnt++;
  sprintf(buf, "%02d", cnt);
  FILE *F = freopen(buf, "wt", stdout);
  assert(F);
  fprintf(stderr, "Write file %02d\n", cnt);
  fflush(stderr);
}

void GoSystem( const char *s, ... )
{
  static char cmd[maxLen];
  GET_ARG(s, cmd)
  fprintf(stderr, "Generator = '%s'\n", cmd);

  static char tmps[maxLen];
  sprintf(tmps, PREFIX"%s > "TMP_FILE, cmd);
  ASSERT(system(tmps) == 0, "SYSTEM CALL FAILED");
  ReadFile(TMP_FILE);
  system(DEL_COMMAND" "TMP_FILE);
}

/* Main part */

const int maxC = (int)1e4;
const int maxN = (int)5e4;

int N, M, C;
int x[maxN], y[maxN];
int a[maxN], b[maxN], c[maxN];

void Out()
{
  NewTest(); // This line creates new test
  printf("%d %d %d\n", N, M, C);
  forn(i, N)
    printf("%d %d\n", x[i], y[i]);
  forn(i, M)
    printf("%d %d %d\n", a[i], b[i], c[i]);
}

void ReadFile( const char *fileName ) // Reads all tests from file
{
  FILE *F;
  ASSERT(!!(F = fopen(fileName, "rt")), "Opening of the file '%s' failed", fileName);

  while (fscanf(F, "%d%d%d", &N, &M, &C) == 3)
  {
    forn(i, N)
      assert(fscanf(F, "%d%d", &x[i], &y[i]) == 2);
    forn(i, M)
      assert(fscanf(F, "%d%d%d", &a[i], &b[i], &c[i]) == 3);
    Out();
  }
  fclose(F);
}

void GenPnt()
{
  forn(i, N)
    x[i] = R(0, C), y[i] = R(0, C);
}

void GenRandom( int n, int m, int cc )
{
  N = n, M = m, C = cc;
  GenPnt();
  forn(i, M)
  {
    do {
      a[i] = R(-C, C);
      b[i] = R(-C, C);
      c[i] = R(-C, C);
    } while (!a[i] && !b[i]);
  }
  Out();
}

void GenMax1( int n, int m )
{
  N = m, M = m, C = maxC / 10;
  GenPnt();
  forn(i, M)
  {
    do {
      a[i] = R(-1, 1);
      b[i] = R(-1, 1);
      int x = R(-100, 100) + C / 2;
      c[i] = -(a[i] * x + b[i] * x);
    } while ((!a[i] && !b[i]) || !(-maxC <= c[i] && c[i] <= maxC));
  }
  Out();
}

void GenMax2( int n, int m )
{
  N = m, M = m, C = maxC / 10;
  GenPnt();
  int x[] = {0, 0, C, C};
  int y[] = {0, C, 0, C};
  forn(i, M)
  {
    int px, py, j;
    do {
      a[i] = R(-2, 2);
      b[i] = R(-2, 2);
      j = R(0, 3);
      px = x[j] + R(-2, 2);
      py = y[j] + R(-2, 2);
      c[i] = -(a[i] * px + b[i] * py);
    } while ((!a[i] && !b[i]) || !(0 <= px && px <= C && 0 <= py && py <= C) || !(-maxC <= c[i] && c[i] <= maxC));
  }
  Out();
}

void GenMax3( int n, int m, int cc )
{
  N = m, M = m, C = cc;
  GenPnt();
  forn(i, M)
  {
    a[i] = 1;
    b[i] = -1;
    c[i] = 0;
  }
  Out();
}

int main()
{
  initrand(RAND_SEED);

  ReadFile("01.sample");
  ReadFile("02.hand");

  for (int n = 5; n <= maxN; n *= 10)
    forn(i, 3)
      GenRandom(n, n, min(n, maxC));

  GenRandom(maxN, maxN, 100);
  GenRandom(maxN, maxN, 10);
  GenRandom(maxN, maxN, 1);

  GenMax1(maxN, maxN);
  GenMax2(maxN, maxN);
  GenMax3(maxN, maxN, 100);
  GenMax3(maxN, maxN, 1);
  return 0;
}
