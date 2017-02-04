#include <cstdio>
#include <cstring>
#include <cassert>

using namespace std;

#define forn(i, n) for (int i = 0; i < n; i++)

template <const int N = 250000>
struct SuffixArray {
  int p[N], p2[N]; // p2 * p = id
  int len[N]; // LCP

  template <class T>
  void BuildArray( int n, T *s ) { // O(NlogN)
    static int num[N + 1], col[N];
    int ma = n, t, cc = 0;
    forn(i, n)
      ma = max(ma, t = s[i]), assert(0 <= t && t < N);
    forn(i, n)
      col[i] = s[i], p[i] = i;

    for (int k2 = 1; k2 / 2 < n && cc != n - 1; k2 *= 2) {
      int k = k2 / 2;
      memset(num, 0, sizeof(num[0]) * (ma + 1));
      forn(i, n)
        num[col[i] + 1]++;
      forn(i, ma)
        num[i + 1] += num[i];
      forn(i, n)
        p2[num[col[(p[i] - k + n) % n]]++] = (p[i] - k + n) % n;
      cc = 0;
      forn(i, n) {
        cc += (i && (col[p2[i]] != col[p2[i - 1]] || col[(p2[i] + k) % n] != col[(p2[i - 1] + k) % n]));
        num[p2[i]] = cc;
      }
      forn(i, n)
        p[i] = p2[i], col[i] = num[i];
    }
    forn(i, n)
      p2[p[i]] = i;
  }

  template <class T>
  void BuildLCP( int n, T *s ) { // O(N), works only for s with no nontrivial period
    int lcp = 0;
    forn(i, n) {
      int j = p2[i];
      if (--lcp < 0)
        lcp = 0;
      if (j != n - 1)
        while (lcp < n && s[(p[j] + lcp) % n] == s[(p[j + 1] + lcp) % n])
          lcp++;
      len[j] = lcp;
    }
  }
};