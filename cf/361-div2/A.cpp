#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

map< int, pair<int, int> > pos;

pair<int, int> operator - (pair<int, int> a, pair<int, int> b) {
  return make_pair(a.fi - b.fi, a.se - b.se);
}

pair<int, int> operator + (pair<int, int> a, pair<int, int> b) {
  return make_pair(a.fi + b.fi, a.se + b.se);
}

int main() {
  pos[1] = {0, 0};
  pos[2] = {0, 1};
  pos[3] = {0, 2};
  pos[4] = {1, 0};
  pos[5] = {1, 1};
  pos[6] = {1, 2};
  pos[7] = {2, 0};
  pos[8] = {2, 1};
  pos[9] = {2, 2};
  pos[0] = {3, 1};

  map< pair<int, int>, int > rf;
  for (auto x : pos) {
    rf[x.se] = x.fi;
  }

  int n;
  cin >> n;

  string s;
  cin >> s;

  vector< pair<int, int> > vc(n - 1);
  for (int i = 1; i < n; i++) {
    int pr = s[i - 1] - '0';
    int nx = s[i] - '0';
    vc[i - 1] = pos[nx] - pos[pr];
  }

  int cnt = 0;
  for (int i = 0; i <= 9; i++) {
    auto cur = pos[i];
    bool ok = true;
    for (int j = 0; j < n - 1; j++) {
      auto nxt = cur + vc[j];
      if (rf.find(nxt) == rf.end()) {
        ok = false;
        break;
      }
      cur = nxt;
    }
    cnt += ok;
  }

  if (cnt == 1) puts("YES");
  else puts("NO");
}
