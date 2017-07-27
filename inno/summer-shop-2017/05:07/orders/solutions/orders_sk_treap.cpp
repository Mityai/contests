/**
 * Status: OK, 1.484 sec
 *
 * ^ query in O(log^2) time
 * ? query in O(log^2) time
 */

#include <cassert> 
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std; 

#ifdef _WIN32
#  define I64 "%I64d"
#else
#  define I64 "%Ld"
#endif

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long long ll;

struct Treap
{
  static const int inf = (int)2e9 + 1;

  struct tree;
  typedef tree* ptree;
  struct tree
  {
    int x, cnt, y;
    ll sum;
    ptree l, r;
  };

  ptree NewT( int x, int cnt, int y )
  {
    ptree t = new tree;
    t->x = x, t->cnt = cnt, t->y = y;
    t->sum = (ll)x * cnt;
    t->l = t->r = 0;
    return t;
  }

  ll Sum( ptree t )
  {
    return t ? t->sum : 0;
  }

  void Calc( ptree t )
  {
    if (t)
      t->sum = (ll)t->x * t->cnt + Sum(t->l) + Sum(t->r);
  }

  void Split( ptree t, ptree &l, ptree &r, int x ) // < x and >= x
  {
    if (!t)
      l = r = 0;
    else if (t->x < x)
      l = t, Split(t->r, t->r, r, x);
    else
      r = t, Split(t->l, l, t->l, x);
    Calc(l), Calc(r);
  }

  void Merge( ptree &t, ptree l, ptree r )
  {
    if (!l)
      t = r;
    else if (!r)
      t = l;
    else if (l->y < r->y)
      t = l, Merge(t->r, t->r, r);
    else
      t = r, Merge(t->l, l, t->l);
    Calc(t);
  }

  ll Sum( ptree t, int vl, int vr, int l, int r )
  {
    if (!t || vl > r || l > vr)
      return 0;
    if (l <= vl && vr <= r)
      return t->sum;
    return Sum(t->l, vl, t->x - 1, l, r) + Sum(t->r, t->x + 1, vr, l, r) + (l <= t->x && t->x <= r ? t->x : 0);
  }

  void Clear( ptree &v )
  {
    if (!v)
      return;
    Clear(v->l);
    Clear(v->r);
    delete v;
    v = 0;
  }

  ptree Find( int x )
  {
    ptree t = root;
    while (t && t->x != x)
      t = (x < t->x ? t->l : t->r);
    return t;
  }

  ptree root;

  Treap() { root = 0; }

  void Clear()
  {
    Clear(root);
  }

  void Add( int x, int cnt )
  {
    assert(cnt);
    ll dsum = (ll)x * cnt;
    if (Find(x))
    {
      ptree t = root;
      while (t->x != x)
      {
        t->sum += dsum;
        t = t->x < x ? t->r : t->l;
      }
      t->cnt += cnt;
      Calc(t);
    }
    else
    {
      ptree *t = &root;
      int y = (rand() << 15) | rand();
      while (*t && (*t)->x != x && (*t)->y < y)
      {
        (*t)->sum += dsum;
        t = ((*t)->x < x ? &(*t)->r : &(*t)->l);
      }
      ptree l, r;
      Split(*t, l, r, x);
      *t = NewT(x, cnt, y);
      (*t)->l = l, (*t)->r = r;
      Calc(*t);
    }
  }

  ll Sum( int l, int r )
  {
    return Sum(root, -inf, inf, l, r);
  }

  void Erase( int x, int cnt )
  {
    assert(cnt);
    ptree *t = &root;
    ll dsum = (ll)x * cnt;
    while (*t && (*t)->x != x)
    {
      (*t)->sum -= dsum;
      if (x < (*t)->x)
        t = &(*t)->l;
      else
        t = &(*t)->r;
    }
    if (((*t)->cnt -= cnt) == 0)
    {
      ptree p = *t;
      Merge(*t, (*t)->l, (*t)->r);
      delete p;
    }
    else
      Calc(*t);
  }

  void Change( int x, int y, int k )
  {
    assert(k > 0);
    Erase(x, k);
    Add(y, k);
  }

  ptree getMin()
  {
    ptree p = root;
    while (p->l)
      p = p->l;
    return p;
  }
};

const int maxn = 1 << 17;

int n, k, L, R;
int val[maxn * 2];
Treap m[maxn * 2];
ll sum;

void do_up( int v, int x, int change )
{
  if (val[v] >= x)
    return;
  val[v] = x;
  int cnt = 0;
  vector <pair<int,int> > t;
  Treap::tree *p;
  while (m[v].root && (p = m[v].getMin())->x < x)
  {
    cnt += p->cnt;
    t.push_back(make_pair(p->x, p->cnt));
    m[v].Erase(p->x, p->cnt);
  }
  if (cnt)
    m[v].Add(x, cnt);
  if (change)
    forn(i, t.size())
      for (int p = v / 2; p >= 1; p /= 2)
        m[p].Change(t[i].first, x, t[i].second);
}

void add( int v, int vL, int vR, int up, int x )
{
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
  if (vL > R || L > vR)
    return;
  do_up(v, x, 0);
  x = max(x, val[v]);
  if (L <= vL && vR <= R)
  {
    sum += m[v].root->sum;
    return;
  }    

  int vM = (vL + vR) >> 1;
  get(2 * v, vL, vM, x);
  get(2 * v + 1, vM + 1, vR, x);
}

void build( int v, int vl, int vr )
{
  m[v].Clear();
  m[v].Add(0, vr - vl + 1);
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
