// 20 points (TL) by Sergey Kopeliovich
// TL 22, >5 sec

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

const int maxn = 2 * maxN;

int n, a[maxn];

void Start( int _n, mas _a )
{
  int i;
  n = _n;
  for (i = 0; i < n; i++)
    a[i] = _a[i];
}

void Add( int i, int x )
{
  //int j;
  memmove(a + i + 1, a + i, (n - i) * sizeof(a[0]));
  //for (j = n; j > i; j--)
  //  a[j] = a[j - 1];
  a[i] = x, n++;
}

void Del( int i )
{
  //int j;
  n--;
  memmove(a + i, a + i + 1, (n - i) * sizeof(a[0]));
  //for (j = i + 1; j < n; j++)
  //  a[j - 1] = a[j];
}

int Get( int L, int R, int x )
{
  int cnt = 0;
  while (L <= R)
    cnt += a[L++] <= x;
  return cnt;
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
