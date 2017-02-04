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

bool less1 (pair <int, int> a, pair <int, int> b)
{
 return a.second - a.first < b.second - b.first;
}

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
  vector <pair <int, int> > v;
  for (i = 0; i < n; i++)
   v.push_back (make_pair (l[i], r[i]));
  sort (v.begin (), v.end (), less1);
  res = 0;
  memset (b, 0, sizeof (b));
  for (i = 0; i < n; i++)
  {
   for (j = 0; j < i; j++)
   {
    int lo, hi;
    lo = v[i].first > v[j].first ? v[i].first : v[j].first;
    hi = v[i].second < v[j].second ? v[i].second : v[j].second;
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
