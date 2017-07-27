/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2012.02.12
 */

#include <ctime>
#include <cmath>
#include <cstdio>
#include <cassert>

#include <vector>
#include <map>

using namespace std;

#define NAME "semiplane"

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define forit(i, a) for (__typeof((a).begin()) i = (a).begin(); i != (a).end(); i++)
#define mp make_pair
#define sz(a) (int)(a).size()
#define pb push_back

typedef pair <int, int> pii;

const int maxN = (int)5e4;
const int maxK = 230;

int k, step, n, m, C;
vector < pair<pii, int> > v[maxK][maxK];
int num[maxK][maxK];
int sum[maxK][maxK];
int a, b, c, cnt;
map <pii, int> Map;

int cnt1, cnt2;

void Use( vector < pair<pii, int> > &v )
{
  cnt2 += sz(v) + 1;
  forn(i, sz(v))
    if  (a * v[i].first.first + b * v[i].first.second + c >= 0)
      cnt += v[i].second;
}

int main()
{
#ifdef DEBUG
  double tmp_start = clock();
  fprintf(stderr, "Start\n");
#endif

  assert(freopen(NAME ".in", "r", stdin));
  assert(freopen(NAME ".out", "w", stdout));

  scanf("%d%d%d", &n, &m, &C), C++;
  k = max(1, (int)(sqrt(n) / 2));
  step = (int)((C + k - 1) / k);
  k = min(k, C / step + 1);
  fprintf(stderr, "n = %d, m = %d, C = %d, k = %d, step = %d\n", n, m, C, k, step);
  forn(i, n)
  {
    int x, y;
    scanf("%d%d", &x, &y);
    Map[mp(x, y)]++;
  }
  forit(it, Map)
  {
    int x = it->first.first;
    int y = it->first.second;
    int k = it->second;
    v[y / step][x / step].pb(mp(mp(x, y), k));
    num[y / step][x / step] += k;
  }
  forn(i, k)
    forn(j, k)
      sum[i][j + 1] = sum[i][j] + num[i][j];

  forn(i, m)
  {
    scanf("%d%d%d", &a, &b, &c);
    cnt = 0;
    cnt1 += k;
    if (a == 0)
    {
      int y = (int)floor((double)-c / b / step);
      forn(i, k)
        if (i == y)
          forn(j, k)
            Use(v[i][j]);
        else if ((i > y) ^ (b < 0))
          cnt += sum[i][k];
    }
    else
    {
      int A = a * step, B = b * step, LY = -c, RY = -c - (step - 1) * b;
      forn(i, k)
      {
        int lx = LY / A, rx = RY / A;
        LY -= B, RY -= B;
        if (rx < lx)
          swap(lx, rx);
        lx = max(min(lx, k), 0);
        rx = max(min(rx, k - 1), -1);
        if (a > 0)
          cnt += sum[i][k] - sum[i][rx + 1];
        else
          cnt += sum[i][lx];        
        while (lx < k && lx <= rx)
          Use(v[i][lx++]);
      }
    }
    printf("%d\n", cnt);
  }

#ifdef DEBUG
  fprintf(stderr, "Total time = %.2lf\n", (clock() - tmp_start) / CLOCKS_PER_SEC);
  fprintf(stderr, "cnt1 = %d, cnt2 = %d\n", cnt1, cnt2);
#endif
  return 0;
}
