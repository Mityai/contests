/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2012.02.12
 */

#include <ctime>
#include <cstdio>
#include <cassert>

#include <map>
#include <vector>
#include <algorithm>

using namespace std;

#define NAME "semiplane"

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define forit(i, a) for (__typeof((a).begin()) i = (a).begin(); i != (a).end(); i++)
#define all(a) (a).begin(), (a).end()
#define sz(a) (int)(a).size()
#define pb push_back

typedef long long ll;

int n, m;
map <int, vector<int> > row;

inline ll SMod( ll x, ll y ) { ll a = x % y; return a < 0 ? a + y : a; }
inline ll DivUp( ll x, ll y ) { return y < 0 ? DivUp(-x, -y) : (x + (y - SMod(x, y)) % y) / y; }
inline ll DivDown( ll x, ll y ) { return y < 0 ? DivDown(-x, -y) : (x - SMod(x, y)) / y; }

int main()
{
#ifdef DEBUG
  double tmp_start = clock();
  fprintf(stderr, "Start\n");
#endif

  assert(freopen(NAME ".in", "r", stdin));
  assert(freopen(NAME ".out", "w", stdout));

  scanf("%d%d%*d", &n, &m);
  forn(i, n)
  {
    int x, y;
    scanf("%d%d", &x, &y);
    row[y].pb(x);
  }
  forit(it, row)
    sort(all(it->second));
  fprintf(stderr, "there %d rows, we should proceed %d queries\n", sz(row), m);
  forn(i, m)
  {
    int a, b, c, cnt = 0;
    scanf("%d%d%d", &a, &b, &c);
    forit(it, row)
    {
      int y = it->first;
      vector <int> &v = it->second;

      ll tmp = (ll)b * y + c;
      if (a == 0)
        cnt += sz(v) * (tmp >= 0);
      else if (a > 0)
        cnt += v.end() - lower_bound(all(v), DivUp(-tmp, a));
      else
        cnt += lower_bound(all(v), DivUp(tmp + 1, -a)) - v.begin();
    }
    printf("%d\n", cnt);
  }

#ifdef DEBUG
  fprintf(stderr, "Total time = %.2lf\n", (clock() - tmp_start) / CLOCKS_PER_SEC);
#endif
  return 0;
}
