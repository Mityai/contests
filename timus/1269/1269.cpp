#include <bits/stdc++.h>
using namespace std;

const int MAXLEN = 1e4;
const int ROOT = 1;

int tc = 1;
vector<int> sufflink(2), uplink(2), par(2, 1), col(2), leaf(2), depth(2);
vector< map<int, int> > nxt(2), go(2);

int f = 0;
unordered_map<char, int> to;

int toint(char c) {
  if (to.find(c) == to.end()) to[c] = f++;
  return to[c];
}

void add(string &s) {
  int node = ROOT, d = 0;
  for (char c : s) {
    int x = toint(c);
    ++d;
    if (nxt[node].find(x) == nxt[node].end()) {
      nxt[node][x] = ++tc;
      nxt.push_back(map<int, int>());
      go.push_back(map<int, int>());
      sufflink.push_back(0);
      uplink.push_back(0);
      par.push_back(node);
      col.push_back(c);
      leaf.push_back(0);
      depth.push_back(d);
    }
    node = nxt[node][x];
  }
  leaf[node] = true;
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
  if (go[v].find(c) == go[v].end()) {
    if (nxt[v].find(c) != nxt[v].end()) {
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
    if (leaf[getSuffLink(v)]) {
      uplink[v] = getSuffLink(v);
    } else if (v == ROOT) {
      uplink[v] = ROOT;
    } else {
      uplink[v] = getUpLink(getSuffLink(par[v]));
    }
  }
  return uplink[v];
}

int process(string &s) {
  int ret = -1;
  int node = ROOT;
  for (int i = 0; i < (int)s.length(); i++) {
    int x = toint(s[i]);
    node = getLink(node, x);
    int cur = node;
    while (cur != ROOT) {
      if (leaf[cur]) {
        ret = i - depth[cur] + 1;
        break;
      }
      cur = getUpLink(cur);
    }
    if (ret != -1) break;
  }
  return ret;
}

int main() {
#if __APPLE__
  freopen("1269.in", "r", stdin);
  freopen("1269.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);

  string s;
  getline(cin, s);
  for (int i = 0; i < n; i++) {
    getline(cin, s);
    add(s);
  }

  int m;
  scanf("%d", &m);

  getline(cin, s);
  for (int i = 0; i < m; i++) {
    getline(cin, s);
    int cur = process(s);
    if (cur != -1) {
      printf("%d %d\n", i + 1, cur + 1);
      return 0;
    }
  }

  puts("Passed");
}
