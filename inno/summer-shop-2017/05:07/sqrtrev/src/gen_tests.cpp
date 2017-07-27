#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <cstdarg>
#include <cmath>

#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

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
#define sz(a) (int)(a).size()
#define pb push_back

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

void ReadFile( const char *fileName ) // Reads all tests from file
{
  FILE *F;
  ASSERT(!!(F = fopen(fileName, "rt")), "Opening of the file '%s' failed", fileName);

  int N;
  while (fscanf(F, "%d", &N) == 1)
  {
    NewTest();
    printf("%d\n", N);
    forn(i, N)
    {
      int x;
      fscanf(F, "%d", &x);
      printf("%d%c", x, " \n"[i == N - 1]);
    }
    fscanf(F, "%d", &N);
    printf("%d\n", N);
    forn(i, N)
    {
      char com[9];
      int a, b, c;
      fscanf(F, "%s%d%d", com, &a, &b);
      if (strcmp(com, "reverse"))
      {
        fscanf(F, "%d", &c);
        printf("%s %d %d %d\n", com, a, b, c);
      }
      else
        printf("%s %d %d\n", com, a, b);
    }
  }
  fclose(F);
}

const int maxN = (int)1e5;
const int maxQ = (int)1e5;
const int maxC = (int)1e9;

void GenRandom( int n, int m, int c )
{
  NewTest();
  printf("%d\n", n);
  forn(i, n)
    printf("%d%c", R(0, c), " \n"[i == n - 1]);
  printf("%d\n", m);
  while (m--)
  {
    int type = R(0, 2);
    int l = R(1, n), r = R(1, n), x = R(0, c);
    if (l > r)
      swap(l, r);
    if (type == 0) printf("reverse %d %d\n", l, r);
    if (type == 1) printf("get %d %d %d\n", l, r, x);
    if (type == 2) printf("set %d %d %d\n", l, r, x);
  }
}

void GenReverse( int n, int m, int c, int k )
{
  NewTest();
  printf("%d\n", n);
  forn(i, n)
    printf("%d%c", R(0, c), " \n"[i == n - 1]);
  printf("%d\n", m);
  forn(i, m)
  {
    int l = R(1, n), r = R(1, n), x = R(0, c);
    if (l > r)
      swap(l, r);
    if (i < k)
      printf("reverse %d %d\n", l, r);
    else
      printf("get %d %d %d\n", l, r, x);
  }
}

void GenSet( int n, int m, int c, int k )
{
  NewTest();
  printf("%d\n", n);
  forn(i, n)
    printf("%d%c", R(0, c), " \n"[i == n - 1]);
  printf("%d\n", m);
  forn(i, m)
  {
    int l = R(1, n), r = R(1, n), x = R(0, c);
    if (l > r)
      swap(l, r);
    if (i < k)
      printf("set %d %d %d\n", l, r, x);
    else
      printf("get %d %d %d\n", l, r, x);
  }
}

void GenSetShort( int n, int m, int c )
{
  NewTest();
  printf("%d\n", n);
  forn(i, n)
    printf("%d%c", R(0, c), " \n"[i == n - 1]);
  printf("%d\n", m);
  forn(i, m)
  {
    if (i < m / 2)
    {
      int l = R(1, n - 1), x = R(0, c);
      printf("set %d %d %d\n", l, l + 1, x);
    }
    else
    {
      int l = R(1, n), r = R(1, n), x = R(0, c);
      if (l > r)
        swap(l, r);
      printf("get %d %d %d\n", l, r, x);
    }
  }
}

void GenAntiLinear( int n, int m, int c, int f )
{
  NewTest();
  printf("%d\n", n);
  forn(i, n)
    printf("%d%c", R(0, c), " \n"[i == n - 1]);
  printf("%d\n", m);
  while (m--)
  {
    int type;
    if (f == 0) type = R(0, 1);
    else type = (f == 1) ^ (m == 0);
    int l = R(1, n / 10), r = R(n - n / 10, n), x = R(0, c);
    if (type == 0) printf("reverse %d %d\n", l, r);
    if (type == 1) printf("get %d %d %d\n", l, r, x);
  }
}

int main()
{
  initrand(RAND_SEED);

  ReadFile("01.sample");
  ReadFile("02.hand");

  GenRandom(10, 100, 100);
  GenRandom(10, maxQ, 2);
  GenRandom(10000, 10000, 100);

  GenRandom(maxN, maxQ, maxC);
  GenReverse(maxN, maxQ, maxC, maxQ / 2);
  GenReverse(maxN, maxQ, maxC, maxQ - 1);
  GenSet(maxN, maxQ, maxC, maxQ / 2);
  GenSet(maxN, maxQ, maxC, maxQ - 1);
  GenSetShort(maxN, maxQ, maxC);
  forn(t, 3)
    GenAntiLinear(maxN, maxQ, maxC, t);
  return 0;
}
