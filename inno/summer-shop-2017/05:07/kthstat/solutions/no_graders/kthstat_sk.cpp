/**
 * 100 points by Sergey Kopeliovich
 * OK
 */

#define DEBUG

#ifdef DEBUG
#  define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#  define debug(x) cerr << #x = ""
#else
#  define err(...) 
#  define debug(x) 
#endif

/** grader.h */

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define maxN 100000

typedef int mas[maxN];

void Start( int n, mas a );
void Add( int i, int x );
void Del( int i );
int Get( int L, int R, int x );

/** solution.cpp */

#include <vector>
#include <algorithm>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef vector <int> vi;

const int LEN = 100;
const int K = 2 * maxN / LEN;

int pn, n, new_n, a[maxN], b[maxN];

struct Part {
  int i, n;
  vi *b;

  Part() {
    b = new vi();
  }

  void calc() {
    err("calc: i=%d, n=%d: ", i, n);
    b->resize(n);
    forn(j, n)
      err("%d ", a[i + j]);
    err(": ");
    copy(a + i, a + i + n, b->begin());
    forn(j, n)
      err("%d ", (*b)[j]);
    err(": ");
    sort(b->begin(), b->end());
    forn(j, n)
      err("%d ", (*b)[j]);
    err("\n");
  }
 void init( int _i, int _n ) {
    i = _i, n = _n, calc();
  }
  int get( int x ) {
    return upper_bound(b->begin(), b->end(), x) - b->begin();
  }
};

Part tmp, p[K + 10];

void out() {
  forn(i, pn) {
    err("%d,%d,%p,[", p[i].i, p[i].n, p[i].b);
    forn(j, p[i].n)
      err("%d%c", a[p[i].i + j], " ;"[j == p[i].n - 1]);
    forn(j, p[i].n)
      err("%d%c", (*p[i].b)[j], " ]"[j == p[i].n - 1]);
    err(" ");
  }
  err("\n");
}

void doCheck() {
  forn(i, pn + 1)
    err("%p ", p[i].b);
  err("\n");
  forn(i, pn + 1)
    forn(j, i)
      if (p[i].b == p[j].b) {
        err("failed: %d %d\n", i, j);
        exit(1);
      }
}

int split( int i ) {
  int j = 0;
  while (j < pn && i >= p[j].n)
    i -= p[j++].n;
  if (i) {
    err("Split: j = %d, i = %d, pn = %d [%d]\n", j, i, pn, pn - j - 1);
    err("before rotation: "), out();
    doCheck();
    if (pn - j > 0)
      tmp = p[pn], memmove(p + j + 1, p + j, sizeof(p[0]) * (pn - j)), p[j] = tmp;
    else
      tmp = p[j];
    doCheck();
    pn++;
    doCheck();
    err("after  rotation: "), out();
    doCheck();
    p[j + 1].i += i, p[j + 1].n = tmp.n - i;
    p[j].n = i, p[j].i = tmp.i;
    p[j].calc(), p[j + 1].calc();
    doCheck();
    j++;
  }
  return j;
}

void build()
{
  err("build!\n");
  new_n = n, pn = 0;
  for (int i = 0; i < n; i += LEN)
    p[pn++].init(i, min(LEN, n - i));
}

inline void check()
{
  if (pn <= K)
    return;
  err("check: need rebuild\n");
  n = 0;
  forn(i, pn)
    forn(j, p[i].n)
      b[n++] = a[p[i].i + j];
  memcpy(b, a, sizeof(b[0]) * n);
  build();
}

void Start( int _n, mas _a )
{
  n = _n, memcpy(a, _a, sizeof(a[0]) * n);
  build();
}

void Add( int i, int x )
{
  i = split(i);
  err("Add: i = %d, pn = %d\n", i, pn);
  pn++;
  if (pn - i > 0)
    tmp = p[pn], memmove(p + i + 1, p + i, (pn - i) * sizeof(p[0])), p[i] = tmp;
  a[new_n] = x;
  p[i].init(new_n++, 1);
  doCheck();
  check();
}

void Del( int i )
{
  i = split(i), split(i + 1);
  err("Del: i = %d, pn = %d\n", i, pn);
  pn--;
  if (pn - i > 0)
    tmp = p[i], memmove(p + i, p + i + 1, (pn - i) * sizeof(p[0])), p[pn] = tmp;
  doCheck();
  check();
}

int Get( int L, int R, int x )
{
  int res = 0;
  err("Get: L = %d, R = %d\n", L, R);
  L = split(L), R = split(R + 1);
  err("Get: L = %d, R = %d\n", L, R);
  for (; L < R; L++)            
    res += p[L].get(x);
  check();
  return res;
}

/** grader.cpp */

int main()
{
  static int n, a[maxN];
  long start = clock();
  int i;

  assert(freopen("kthstat.in", "r", stdin));
  assert(freopen("kthstat.out", "w", stdout));

  scanf("%d", &n);
  for (i = 0; i < n; i++)
    scanf("%d", &a[i]);

  Start(n, a);

  char type;
  int x, y, z, tn = 0;
  while (scanf(" %c", &type) == 1)
  {
    doCheck();
    out();
    if (type == '+')
      scanf("%d%d", &x, &y), Add(x, y);
    else if (type == '-')
      scanf("%d", &x), Del(x);
    else if (type == '?')  
      scanf("%d%d%d", &x, &y, &z), printf("%d\n", Get(x, y, z));
    else
    {
      fprintf(stderr, "Unknown option: %c\n", type);
      exit(3128);
    }
    tn++;
  }
  fprintf(stderr, "OK, %d tests, time = %.2lf\n", tn, (double)(clock() - start) / CLOCKS_PER_SEC);
  return 0;
}
