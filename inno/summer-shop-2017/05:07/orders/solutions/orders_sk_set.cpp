/**
 * Status: TL 25, >3 sec
 *
 * ^ query in O(log^2) time
 * ? query in O(log^2 + n) time
 */

#include <cassert> 
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>

using namespace std; 

#ifdef _WIN32
#  define I64 "%I64d"
#else
#  define I64 "%Ld"
#endif

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long long ll;

const int maxn = 1 << 17;

int n, k, L, R;
int val[maxn * 2];
map <int, int> m[maxn * 2];
ll sum;

void change_v( int v, int x, int y, int k )
{
  int r = m[v][x] -= k;
  assert(r >= 0);
  if (!r)
    m[v].erase(x);
  m[v][y] += k;
}

void do_up( int v, int x, int change )
{
  if (val[v] >= x)
    return;
  val[v] = x;
  int cnt = 0;
  vector <pair<int,int> > t;
  for (map <int, int>::iterator it = m[v].begin(); it != m[v].end() && it->first < x; it++)
    t.push_back(*it);
  forn(i, t.size())
    m[v].erase(t[i].first), cnt += t[i].second;
  m[v][x] += cnt;
  if (change)
    forn(i, t.size())
      for (int p = v / 2; p >= 1; p /= 2)
        change_v(p, t[i].first, x, t[i].second);
}

void add( int v, int vL, int vR, int up, int x )
{
  assert(1 <= v && v < maxn * 2);
  
  if (vL > R || L > vR)
    return;
  do_up(v, up, 0);
  if (L <= vL && vR <= R)
  {
    do_up(v, x, 1);
    return;
  }

  int vM = (vL + vR) >> 1;
  up = max(up, val[v]);
  add(2 * v, vL, vM, up, x);
  add(2 * v + 1, vM + 1, vR, up, x);
}

void get( int v, int vL, int vR, int x )
{
  assert(1 <= v && v < maxn * 2);

  if (vL > R || L > vR)
    return;
  do_up(v, x, 0);
  x = max(x, val[v]);
  if (L <= vL && vR <= R)
  {
    for (map <int, int>::iterator it = m[v].begin(); it != m[v].end(); it++)
      sum += (ll)max(it->first, x) * it->second;
    return;
  }    

  int vM = (vL + vR) >> 1;
  get(2 * v, vL, vM, x);
  get(2 * v + 1, vM + 1, vR, x);
}

void build( int v, int vl, int vr )
{
  assert(1 <= v && v < maxn * 2);

  m[v].clear();
  m[v][0] = vr - vl + 1;
  if (vl == vr)
    return;

  int vm = (vl + vr) / 2;
  build(2 * v, vl, vm);
  build(2 * v + 1, vm + 1, vr);
}

int main()
{
  assert(freopen("orders.in", "r", stdin));
  assert(freopen("orders.out", "w", stdout));

  while (scanf("%d%d", &n, &k) == 2 && (n || k))
  {
    int ma = 1, x;
    while (ma <= n)
      ma *= 2;
    assert(ma <= maxn);
    memset(val, 0, sizeof(val[0]) * (ma * 2));
    build(1, 0, n - 1);

    forn(i, k)
    {
      char type;
      scanf(" %c%d%d", &type, &L, &R), L--, R--;
      if (type == '^')
      {
        scanf("%d", &x);
        add(1, 0, n - 1, 0, x);
      }
      else 
      {
        ll cnt = R - L + 1;
        sum = 0;
        get(1, 0, n - 1, 0);

        ll g = __gcd(sum, cnt);
        sum /= g, cnt /= g;
        if (cnt == 1)
          printf(I64"\n", sum);
        else
          printf(I64"/"I64"\n", sum, cnt);
      }
    }
  }
  return 0;
}
