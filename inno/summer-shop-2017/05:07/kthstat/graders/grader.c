#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "grader.h"

static int isRun = 0;

#define maxn (int)2e5

int main()
{
  static int n, a[maxn];
  long start = clock();
  int i;

  if (isRun)
  {
    printf("SV User tries to hack the system");
    exit(3128);
  }
  isRun = 1;

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
      printf("Unknown option: %c\n", type);
      exit(3128);
    }
    tn++;
  }
  printf("OK, %d tests, time = %.2lf\n", tn, (double)(clock() - start) / CLOCKS_PER_SEC);
  return 0;
}
