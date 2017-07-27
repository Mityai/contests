// 60 points (WA) by Sergey Kopeliovich
// WA 25

#include <cstdio>
#include <ctime>
#include <cassert>

#include <algorithm>
#include <vector>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define forab(i, a, b) for (int i = (int)(a); i <= (int)(b); i++)
#define sz(a) (int)(a).size()
#define pb push_back

#define maxN 100000

typedef int mas[maxN];

void Start( int n, mas a );
void Add( int i, int x );
void Del( int i );
int Get( int L, int R, int x );

const int K = 1000;
const int maxn = 2 * maxN + K;
const int M = maxn / K;

int an, a[maxn];
int pos, mem[maxn * 4];
vector <int *> v1, v2;
vector <int> len;

void Build( int n, mas a )
{
  pos = 0;
  v1.clear();
  v2.clear();
  len.clear();
  for (int i = 0; i < n; i += K)
  {
    v1.pb(mem + pos);
    forn(j, K)
      mem[pos++] = a[i + j];
    pos += K;

    v2.pb(mem + pos);
    forn(j, K)
      mem[pos++] = a[i + j];
    sort(mem + pos - K, mem + pos);
    pos += K;

    len.pb(K);
  }
}

void Add( int p, int x )
{
  int i = 0;
  while (len[i] < p)
    p -= len[i++];

  #define INSERT \
    for (int j = n; j > p; j--) \
      a[j] = a[j - 1]; \
    a[p] = x; 

  int &n = len[i], *a = v1[i];
  INSERT
  a = v2[i], p = lower_bound(a, a + n, x) - a;
  INSERT
  n++;
  if (n >= 2 * K)
  {
    an = 0;
    forn(i, sz(v1))
      forn(j, len[i])
        a[an++] = v1[i][j];
    Build(an, a);
  }
}

void Del( int p )
{
  int i = 0;
  while (len[i] <= p)
    p -= len[i++];

  int x = v1[i][p];
  #define ERASE \
    for (int j = p + 1; j < n; j++) \
      a[j - 1] = a[j];

  int &n = len[i], *a = v1[i];
  ERASE
  a = v2[i], p = lower_bound(a, a + n, x) - a;
  ERASE
  n--;
}

int Get( int L, int R, int x )
{
  int i = 0;
  while (len[i] <= L)
    L -= len[i], R -= len[i++];

  int cnt = 0, *a = v1[i], n = len[i];
  if (R < n)
    forab(j, L, R)
      cnt += (a[j] <= x);
  else
  {
    forab(j, L, n - 1)
      cnt += (a[j] <= x);
    R -= n, i++;
    while (len[i] <= R)
    {
      a = v2[i], cnt += lower_bound(a, a + len[i], x + 1) - a;
      R -= len[i++];
    }
    a = v1[i];
    forab(j, 0, R)
      cnt += (a[j] <= x);
  }  
  return cnt;
}

void Start( int n, mas a )
{
  Build(n, a);
}

int main()
{
  static int n, a[maxn];
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