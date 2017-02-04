#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>

#define TASKNAME "segments"

using namespace std;

const int MinN = 1, MaxN = 100000;
const int MinC = 1, MaxC = 1000000000;

int l [MaxN], r [MaxN];
bool b [MaxN];
int n;

int main (void)
{
 int i, j, res;
 freopen (TASKNAME ".in", "rt", stdin);
 freopen (TASKNAME ".out", "wt", stdout);
 while (scanf (" %d", &n) != EOF)
 {
  for (i = 0; i < n; i++)
  {
   scanf (" %d %d", &l[i], &r[i]);
   assert (MinC <= l[i] && l[i] < r[i] && r[i] <= MaxC);
  }
  res = 0;
  memset (b, 0, sizeof (b));
  for (i = 0; i < n; i++)
  {
   for (j = 0; j < i; j++)
   {
    int lo, hi;
    lo = l[i] > l[j] ? l[i] : l[j];
    hi = r[i] < r[j] ? r[i] : r[j];
    if (lo < hi) break;
   }
   if (j == i)
   {
    res++;
    b[i] = true;
   }
  }
  printf ("%d\n", res);
 }
 return 0;
}
