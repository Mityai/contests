#include <bits/stdc++.h>
using namespace std;

const int MAXLEN = 1e3;
const int Q = 1e3;
const int ALPHA = 26;
const int N = MAXLEN * ALPHA;
const int ROOT = 1;

int tc = 1;
int nxt[N][2 * ALPHA], go[N][2 * ALPHA], sufflink[N], uplink[N], par[N], col[N];
bool ans[Q];
vector<int> leafs[N];

void clear() {
  tc = 1;
  memset(nxt, 0, sizeof nxt);
  memset(go, 0, sizeof go);
  memset(sufflink, 0, sizeof sufflink);
  memset(uplink, 0, sizeof uplink);
  memset(par, 0, sizeof par);
  memset(col, 0, sizeof col);
  memset(ans, 0, sizeof ans);
  for (int i = 0; i < N; i++) leafs[i].clear();
}

int toint(char c) {
  if ('a' <= c && c <= 'z') return c - 'a';
  return c - 'a' + 26;
}

void add(string &s, int id) {
  int node = ROOT;
  for (char &c : s) {
    int x = toint(c);
    if (!nxt[node][x]) nxt[node][x] = ++tc, par[tc] = node, col[tc] = x;
    node = nxt[node][x];
  }
  leafs[node].push_back(id);
}

int getLink(int v, int c);

int getSuffLink(int v) {
  if (!sufflink[v]) {
    if (v == ROOT || par[v] == ROOT) {
      sufflink[v] = ROOT;
    } else {
      sufflink[v] = getLink(getSuffLink(par[v]), col[v]);
    }
  }
  return sufflink[v];
}

int getLink(int v, int c) {
  if (!go[v][c]) {
    if (nxt[v][c]) {
      go[v][c] = nxt[v][c];
    } else if (v == ROOT) {
      go[v][c] = ROOT;
    } else {
      go[v][c] = getLink(getSuffLink(par[v]), c);
    }
  }
  return go[v][c];
}

int getUpLink(int v) {
  if (!uplink[v]) {
    if (!leafs[getSuffLink(v)].empty()) {
      uplink[v] = getSuffLink(v);
    } else if (v == ROOT) {
      uplink[v] = ROOT;
    } else {
      uplink[v] = getUpLink(getSuffLink(par[v]));
    }
  }
  return uplink[v];
}

void process(string &s) {
  int node = ROOT;
  for (char c : s) {
    int x = toint(c);
    node = getLink(node, x);
    int cur = node;
    while (cur != ROOT) {
      for (int v : leafs[cur]) {
        ans[v] = true;
      }
      cur = getUpLink(cur);
    }
  }
}

int main() {
#if __APPLE__
  freopen("10679.in", "r", stdin);
  freopen("10679.out", "w", stdout);
#endif

  int k;
  scanf("%d", &k);

  while (k--) {
    clear();

    string s;
    cin >> s;

    int q;
    scanf("%d", &q);

    for (int i = 0; i < q; i++) {
      string t;
      cin >> t;
      add(t, i);
    }

    process(s);
    for (int i = 0; i < q; i++) {
      puts(ans[i] ? "y" : "n");
    }
  }
}
