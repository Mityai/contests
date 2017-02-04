/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#include <cstring>
#include <cassert>

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define zero(a) memset(a, 0, sizeof(a))

template <const int maxV, const int E>
struct AhoCorasic {
  struct Vertex {
    int next[E], p, dep, ch, suf, end;
  };

  int vn;
  Vertex a[maxV];
  int qst, qen, q[maxV];

  int newV( int P, int D, int K ) {
    assert(vn < maxV);
    Vertex &v = a[vn];
    v.dep = D, v.ch = K, v.p = P, v.end = 0;
    zero(v.next);
    return vn++;
  }

  AhoCorasic() {
    vn = 0, newV(-1, 0, -1);
  }

  void add( const char *s ) {
    int v = 0;
    while (*s) {
      int ch = *s++ - 'a', &x = a[v].next[ch];
      if (!x)
        x = newV(v, a[v].dep + 1, ch);
      v = x;
    }
    a[v].end = 1;
  }

  void build() {
    qst = qen = 0;
    q[qen++] = 0;
    while (qst < qen) {
      int v = q[qst++];
      Vertex &V = a[v];
      V.suf = (V.dep <= 1 ? 0 : a[a[V.p].suf].next[V.ch]);
      forn(i, 26)
        if (V.next[i])
          q[qen++] = V.next[i];
        else 
          V.next[i] = a[V.suf].next[i];
      V.end |= a[V.suf].end;
    }
  }
};

AhoCorasic<(int)1e5, 26> m;
