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
int n;

int main (void)
{
 int i, cur, res;
 freopen (TASKNAME ".in", "rt", stdin);
 freopen (TASKNAME ".out", "wt", stdout);
 while (scanf (" %d", &n) != EOF)
 {
  for (i = 0; i < n; i++)
  {
   scanf (" %d %d", &l[i], &r[i]);
   assert (MinC <= l[i] && l[i] < r[i] && r[i] <= MaxC);
  }
  vector <pair <int, int> > v;
  for (i = 0; i < n; i++)
   v.push_back (make_pair (r[i], l[i]));
  sort (v.begin (), v.end ());
  cur = 0;
  res = 0;
  for (i = 0; i < n; i++)
   if (v[i].second >= cur)
   {
    res++;
    cur = v[i].first;
   }
  printf ("%d\n", res);
 }
 return 0;
}
