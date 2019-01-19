#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

struct A {
  long long w, c;
};

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int n, p;
  scanf("%d%d", &n, &p);

  vector<A> a(n);
  for (int i = 0; i < n; ++i) {
    scanf("%lld", &a[i].w);
  }
  long long sum = 0;
  int sump = 0;
  for (int i = 0; i < n; ++i) {
    scanf("%lld", &a[i].c);
    sum += a[i].c;
    sump = (sump + a[i].w) % p;
  }

  vector<vector<A>> bucket(p);

  sort(a.begin(), a.end(), [](const A& l, const A& r) {
    return l.c < r.c;
  });

  for (int i = 0; i < n; ++i) {
    if (bucket[a[i].w % p].size() < 5) {
      bucket[a[i].w % p].push_back(a[i]);
    }
  }

  const long long INF = 1e18;
  vector<long long> d(p, INF);
  d[0] = 0;
  for (int id = 0; id < p; ++id) {
    for (const auto& aa : bucket[id]) {
      vector<long long> d2 = d;
      for (int x = 0; x < p; ++x) {
        if (d[x] != INF) {
          int y = (x + aa.w) % p;
          if (d2[y] > d[x] + aa.c) {
            d2[y] = d[x] + aa.c;
          }
        }
      }
      d.swap(d2);
    }
  }

  vector<long long> ans(p, -1);
  for (int i = 0; i < p; ++i) {
    if (d[i] != INF) {
      int ind = (sump - i) % p;
      if (ind < 0) ind += p;
      ans[ind] = max(ans[ind], sum - d[i]);
    }
  }

  for (size_t i = 0; i < p; ++i) {
    printf("%lld ", ans[i]);
  }
  putchar('\n');
}
