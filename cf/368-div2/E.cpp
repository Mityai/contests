#include <bits/stdc++.h>
#define left aflkajsdf
#define right sdljfkadsk
#define fi first
#define se second
using namespace std;

typedef long long ll;

const int LEN = 7;

int main() {
#if __APPLE__
  freopen("E.in", "r", stdin);
  freopen("E.out", "w", stdout);
#endif

  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);

  int type[n + 2][m + 2];
  memset(type, -1, sizeof type);

  int a[n + 2][m + 2];
  memset(a, 0, sizeof a);

  ll up[n + 2][m + 2], down[n + 2][m + 2], left[n + 2][m + 2], right[n + 2][m + 2]; 
  memset(up, 0, sizeof up);
  memset(down, 0, sizeof down);
  memset(left, 0, sizeof left);
  memset(right, 0, sizeof right);

  int mini[k], maxi[k], minj[k], maxj[k];
  memset(mini, 127, sizeof mini);
  memset(maxi, 0, sizeof maxi);
  memset(minj, 127, sizeof minj);
  memset(maxj, 0, sizeof maxj);

  ll sumall[k];

  for (int id = 0; id < k; id++) {
    int len;
    scanf("%d", &len);

    int i[len], j[len], w[len];
    for (int e = 0; e < len; e++) {
      scanf("%d%d%d", i + e, j + e, w + e);
      a[i[e]][j[e]] = w[e];
      type[i[e]][j[e]] = id;
      mini[id] = min(mini[id], i[e]);
      minj[id] = min(minj[id], j[e]);
      maxi[id] = max(maxi[id], i[e]);
      maxj[id] = max(maxj[id], j[e]);
    }

    ll sumsuf[len];
    for (int e = len - 1; e >= 0; e--) {
      sumsuf[e] = w[e];
      if (e < len - 1) sumsuf[e] += sumsuf[e + 1];
    }
    sumall[id] = sumsuf[0];

    for (int e = 0; e + 1 < len; e++) {
      if (i[e] - 1 == i[e + 1]) {
        up[i[e]][j[e]] = sumsuf[e + 1];
      } else if (i[e] + 1 == i[e + 1]) {
        down[i[e]][j[e]] = sumsuf[e + 1];
      } else if (j[e] - 1 == j[e + 1]) {
        left[i[e]][j[e]] = sumsuf[e + 1];
      } else if (j[e] + 1 == j[e + 1]) {
        right[i[e]][j[e]] = sumsuf[e + 1];
      } else assert(false);
    }
  }

  int q;
  scanf("%d", &q);

  bool on[k];
  memset(on, true, sizeof on);
  for (int i = 0; i < q; i++) {
    char s[LEN];
    scanf(" %s", s);

    if (s[0] == 'S') {
      int x;
      scanf("%d", &x);
      on[x - 1] ^= true;
    } else {
      int i1, j1, i2, j2;
      scanf("%d%d%d%d", &i1, &j1, &i2, &j2);

      ll ans = 0;
      for (int j = 0; j < k; j++) {
        if (on[j]) {
          if (i1 <= mini[j] && maxi[j] <= i2 && j1 <= minj[j] && maxj[j] <= j2) {
            ans += sumall[j];
          }
        }
      }

      vector< vector<ll> > in(k), out(k);
      for (int x = j1; x <= j2; x++) {
        int t = type[i1 - 1][x];
        if (t >= 0 && on[t] && down[i1 - 1][x]) {
          in[t].push_back(down[i1 - 1][x]);
        }
        t = type[i2][x];
        if (t >= 0 && on[t] && a[i2 + 1][x] > 0 && down[i2][x]) {
          out[t].push_back(down[i2][x]);
        }
        t = type[i2 + 1][x];
        if (t >= 0 && on[t] && up[i2 + 1][x]) {
          in[t].push_back(up[i2 + 1][x]);
        }
        t = type[i1][x];
        if (t >= 0 && on[t] && a[i1 - 1][x] > 0 && up[i1][x]) {
          out[t].push_back(up[i1][x]);
        }
      }
      for (int y = i1; y <= i2; y++) {
        int t = type[y][j1 - 1];
        if (t >= 0 && on[t] && right[y][j1 - 1]) {
          in[t].push_back(right[y][j1 - 1]);
        }
        t = type[y][j2];
        if (t >= 0 && on[t] && a[y][j2 + 1] > 0 && right[y][j2]) {
          out[t].push_back(right[y][j2]);
        }
        t = type[y][j2 + 1];
        if (t >= 0 && on[t] && left[y][j2 + 1]) {
          in[t].push_back(left[y][j2 + 1]);
        }
        t = type[y][j1];
        if (t >= 0 && on[t] && a[y][j1 - 1] > 0 && left[y][j1]) {
          out[t].push_back(left[y][j1]);
        }
      }

      for (int j = 0; j < k; j++) {
        ll cur = 0;
        if (!in[j].empty() && !out[j].empty()) {
          sort(in[j].rbegin(), in[j].rend());
          sort(out[j].rbegin(), out[j].rend());
          if (in[j][0] > out[j][0]) {
            for (int f = 0, g = 0; f < (int)in[j].size() || g < (int)out[j].size();) {
              if (f == g) {
                cur += in[j][f];
                f++;
              } else {
                cur -= out[j][g];
                g++;
              }
            }
          } else {
            cur = sumall[j];
            for (int f = 0, g = 0; f < (int)in[j].size() || g < (int)out[j].size();) {
              if (f == g) {
                cur -= out[j][g];
                g++;
              } else {
                cur += in[j][f];
                f++;
              }
            }
          }
        } else if (!in[j].empty()) {
          cur = in[j][0];
        } else if (!out[j].empty()) {
          cur = sumall[j] - out[j][0];
        }
        ans += cur;
      }
      printf("%lld\n", ans);
    }
  }
}
