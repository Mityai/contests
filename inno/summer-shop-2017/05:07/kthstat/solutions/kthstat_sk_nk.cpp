// 20 points (TL) by Sergey Kopeliovich

#include "grader.h"

#define maxn (int)1e5

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
  int j;
  for (j = n; j > i; j--)
    a[j] = a[j - 1];
  a[i] = x, n++;
}

void Del( int i )
{
  int j;
  for (j = i + 1; j < n; j++)
    a[j - 1] = a[j];
  n--;
}

int Get( int L, int R, int x )
{
  int cnt = 0;
  while (L <= R)
    cnt += a[L++] <= x;
  return cnt;
}
