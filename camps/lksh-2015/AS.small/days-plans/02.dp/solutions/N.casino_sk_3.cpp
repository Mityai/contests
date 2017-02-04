/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2014.11.23
 */

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define zero(a) memset(a, 0, sizeof(a))

const int N = 150;
const int L = 150;

int wn, n, len, cost[26], wl[N];
char s[L + 1], w[N][L + 1];
bitset<L+1> is[N][L], can[L], sb[26];
int f[L + 1], sum[L + 1];

int main() {
  #define NAME "casino"
  assert(freopen(NAME ".in", "r", stdin));
  assert(freopen(NAME ".out", "w", stdout));

  scanf("%d", &n);
  while (n--) {
    char ch;
    scanf(" %c", &ch);
    scanf("%d", &cost[ch - 'a']);
  }
  scanf("%s%d", s, &wn), len = strlen(s);
  forn(i, len)
    sb[s[i] - 'a'][i] = 1;
  forn(i, wn)
    scanf("%s", w[i]), wl[i] = strlen(w[i]);
  for (int l = len-1; l >= 0; l--) { // left border
    can[l][l] = 1;
    zero(is);
    forn(j, wn)
      is[j][0][l+1] = (s[l] == w[j][0]);
    for (int k = 1; l+k <= len; k++) { // [l,l+k)
      for (int m = 1; m < k; m++) // [l,l+m) [l+m,l+k)
        if (can[l][l+m] && can[l+m][l+k])
          can[l][l+k] = 1;
      forn(i, wn) 
        if (is[i][wl[i]-1][l+k])
          can[l][l+k] = 1;
      forn(i, wn) 
        forn(j, wl[i]-1)
          if (is[i][j][l+k])
            is[i][j+1] |= (sb[w[i][j+1] - 'a'] & can[l+k]) << 1;
    }
  }
  f[0] = 0, sum[0] = 0;
  for (int i = 1; i <= len; i++) {
    sum[i] = sum[i-1] + cost[s[i-1] - 'a'];
    f[i] = f[i-1];
    forn(j, i)
      if (can[j][i])
        f[i] = max(f[i], f[j] + sum[i] - sum[j]); 
  }
  printf("%d\n", f[len]);
  return 0;
}
