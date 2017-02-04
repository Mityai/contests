/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2015.04.27
 */

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

const int K = 20;
const int N = 1e6;

int k, m, a[K + 1], f[N + 1];

inline int readInt(); 

int main() {
  #define NAME "heaps2"
  assert(freopen(NAME ".in", "r", stdin));
  assert(freopen(NAME ".out", "w", stdout));
  
  k = readInt();
  forn(i, k)
    a[i] = readInt();
  sort(a, a + k);
  a[k] = N + 10;
  for (int i = 1; i <= N; i++)
    for (int j = 0; a[j] <= i; j++)
      if (!f[i - a[j]]) {
        f[i] = 1;
        break;
      }
  m = readInt();
  while (m--) 
    puts(f[readInt()] ? "First" : "Second");
  return 0;
}

/** Read */

static const int buf_size = 4096;

inline int getchar_fast() { // you may use getchar() instead of it
  static char buf[buf_size];
  static int len = 0, pos = 0;
  if (pos == len)
    pos = 0, len = fread(buf, 1, buf_size, stdin);
  if (pos == len)
    return -1;
  return buf[pos++];
}

inline int readChar() {
  int c = getchar_fast();
  while (c <= 32)
    c = getchar_fast();
  return c;
}

inline int readInt() {
  int s = 1, c = readChar();
  int x = 0;
  if (c == '-')
    s = -1, c = getchar_fast();
  while ('0' <= c && c <= '9')
    x = x * 10 + c - '0', c = getchar_fast();
  return s == 1 ? x : -x;
}
