/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#include <cassert>
#include <cstring>

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

template <const int N, const int ALPHA>
struct Automaton {
  static const int VN = 2 * N + 1;
  int root, last, n, len[N], suf[N], next[N][ALPHA];

  inline int newV( int l, int _suf ) {
    assert(n < VN);
    memset(next[n], 0, sizeof(next[n]));
    len[n] = l, suf[n] = _suf;
    return n++;
  }
  void build( const char *s ) {
    forn(i, ALPHA)
      next[0][i] = 1;
    n = 1, root = last = newV(0, 0);
    for (int i = 0; s[i]; i++) {
      int ch = s[i] - 'a';
      int R, Q, P = last;
      last = newV(len[last] + 1, 0);
      while (!next[P][ch])
        next[P][ch] = last, P = suf[P];
      if (!P)
        suf[last] = 1;
      else if (len[Q = next[P][ch]] == len[P] + 1)
        suf[last] = Q;
      else {
        R = newV(len[P] + 1, suf[Q]);
        suf[last] = suf[Q] = R;
        memcpy(next[R], next[Q], sizeof(next[R]));
        while (P && next[P][ch] == Q)
          next[P][ch] = R, P = suf[P];
      }
    }
  }
};

Automaton<3> a;

int main() {
  const char *s = "abc";
  a.build(s);
}
