#include <bits/stdc++.h>
using namespace std;

const int MAXLEN = 1e4;
const int ALPHA = 26;
const int N = MAXLEN * ALPHA;
const int ROOT = 1;

int tc = 1;
int nxt[N][ALPHA], go[N][ALPHA], par[N], col[N], uplink[N], suffixlink[N], leaf[N];

void clear() {
  for (int i = 0; i <= tc; i++) {
    memset(nxt[i], 0, sizeof nxt[i]);
    memset(go[i], 0, sizeof go[i]);
    par[i] = col[i] = uplink[i] = suffixlink[i] = leaf[i] = 0;
  }
  tc = 1;
  par[1] = 1;
}

void add(string &s) {
  int v = ROOT;
  for (char c : s) {
    int x = c - 'a';
    if (!nxt[v][x]) {
      nxt[v][x] = ++tc;
      par[tc] = v;
      col[tc] = x;
    }
    v = nxt[v][x];
  }
  leaf[v]++;
}

int getLink(int v, int c);

int getSuffixLink(int v) {
  if (!suffixlink[v]) {
    if (v == ROOT || par[v] == ROOT) {
      suffixlink[v] = ROOT;
    } else {
      suffixlink[v] = getLink(getSuffixLink(par[v]), col[v]);
    }
  }
  return suffixlink[v];
}

int getLink(int v, int c) {
  if (!go[v][c]) {
    if (nxt[v][c]) {
      go[v][c] = nxt[v][c];
    } else if (v == ROOT) {
      go[v][c] = ROOT;
    } else {
      go[v][c] = getLink(getSuffixLink(v), c);
    }
  }
  return go[v][c];
}

int getUpLink(int v) {
  if (!uplink[v]) {
    if (leaf[getSuffixLink(v)]) {
      uplink[v] = getSuffixLink(v);
    } else if (v == ROOT) {
      uplink[v] = ROOT;
    } else {
      uplink[v] = getUpLink(getSuffixLink(v));
    }
  }
  return uplink[v];
}

int process(string &s) {
  int ret = 0;
  int v = ROOT;
  for (char c : s) {
    int x = c - 'a';
    v = getLink(v, x);
    int cur = v;
    while (cur != ROOT) {
      ret += leaf[cur];
      cur = getUpLink(cur);
    }
  }
  return ret;
}

int main() {
#if __APPLE__
  freopen("B.in", "r", stdin);
  freopen("B.out", "w", stdout);
#endif

  int T;
  scanf("%d", &T);

  while (T--) {
    clear();

    int n, k;
    scanf("%d%d", &n, &k);

    vector<string> a(n);
    for (int i = 0; i < n; i++) {
      cin >> a[i];
    }

    for (int i = 0; i < k; i++) {
      string s;
      cin >> s;
      add(s);
    }

    for (int i = 0; i < n; i++) {
      printf("%d\n", process(a[i]));
    }
  }
}
