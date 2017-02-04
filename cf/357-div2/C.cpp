#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

int main() {
  int n;
  scanf("%d", &n);

  
  vector< pair<string, int> > ans;
  multiset<int> q;
  for (int i = 0; i < n; i++) {
    char s[10];
    scanf(" %s", s);

    if (s[0] == 'i') {
      int x;
      scanf("%d", &x);

      q.insert(x);
      ans.push_back({"insert", x});
    } else if (s[0] == 'g') {
      int x;
      scanf("%d", &x);

      while (!q.empty() && *q.begin() < x) {
        q.erase(q.begin());
        ans.push_back({"removeMin", *q.begin()});
      }
      if (q.empty() || *q.begin() > x) {
        q.insert(x);
        ans.push_back({"insert", x});
      }
      ans.push_back({"getMin", x});
    } else {
      if (q.empty()) {
        ans.push_back({"insert", int(-1e9)});
        q.insert(int(-1e9));
      }
      q.erase(q.begin());
      ans.push_back({"removeMin", 0});
    }
  }

  printf("%d\n", (int)ans.size());
  for (auto v : ans) {
    printf("%s ", v.fi.c_str());
    if (v.fi != "removeMin") {
      printf("%d\n", v.se);
    } else {
      puts("");
    }
  }
}
