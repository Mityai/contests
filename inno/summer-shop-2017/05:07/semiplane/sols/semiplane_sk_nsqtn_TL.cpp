/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2012.02.12
 */

#include <ctime>
#include <cmath>
#include <cstdio>
#include <cassert>

#include <vector>

using namespace std;

#define NAME "semiplane"

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define mp make_pair
#define sz(a) (int)(a).size()
#define pb push_back

typedef pair <int, int> pii;

const int maxN = (int)5e4;
const int maxK = 230;

int k, step, n, m, C;
vector <pii> v[maxK][maxK];
int sum[maxK][maxK];
int a, b, c, cnt;

int cnt1, cnt2;

void Use( vector <pii> &v )
{
  cnt2 += sz(v);
  forn(i, sz(v))
    cnt += (a * v[i].first + b * v[i].second + c >= 0);
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
  k = max(1, (int)(sqrt(n) / 2.5));
  fprintf(stderr, "n = %d, m = %d, C = %d, k = %d\n", n, m, C, k);
  step = (int)((C + k - 1) / k);
  forn(i, n)
  {
    int x, y;
    scanf("%d%d", &x, &y);
    v[y / step][x / step].pb(mp(x, y));
  }
  forn(i, k)
    forn(j, k)
      sum[i][j + 1] = sum[i][j] + sz(v[i][j]);

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
