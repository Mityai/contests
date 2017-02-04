#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAX = 1e9;

struct Q {
  int t, s, p, i;
};

bool operator < (Q q1, Q q2) {
  return q1.p > q2.p;
}

int main() {
#if __APPLE__
  freopen("E.in", "r", stdin);
  freopen("E.out", "w", stdout);
#else
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif

  int n;
  scanf("%d", &n);

  vector<Q> a(n);
  set<int> hs;
  int id = 0;
  for (int i = 0; i < n; i++) {
    scanf("%d%d%d", &a[i].t, &a[i].s, &a[i].p);
    hs.insert(a[i].p);
    a[i].i = i;
    if (a[i].p == -1) id = i;
  }

  ll T;
  scanf("%lld", &T);

  sort(a.begin(), a.end(), [](Q q1, Q q2) { return q1.t < q2.t; });

  vector<int> priors;
  for (int i = 0; i < n; i++) {
    if (a[i].p - 1 >= 1) {
      if (hs.find(a[i].p - 1) == hs.end()) priors.push_back(a[i].p - 1);
    }
    if (a[i].p + 1 <= MAX) {
      if (hs.find(a[i].p + 1) == hs.end()) priors.push_back(a[i].p + 1);
    }
  }
  sort(priors.begin(), priors.end());
  int m = (int)priors.size();

  ll ans[n];
  memset(ans, 0, sizeof ans);
  set<Q> q;

  int lb = 0, rb = m;
  while (lb + 1 < rb) {
    int mb = (lb + rb) / 2;
    ll tm = 0;
    for (int i = 0; i < n; i++) {
      while (tm < a[i].t && !q.empty()) {
        auto cur = *q.begin();
        q.erase(q.begin());
        ll candel = min(a[i].t - tm, (ll)cur.s);
        cur.s -= candel;
        tm += candel;
        if (cur.s == 0) {
          ans[cur.i] = tm;
        } else {
          q.insert(cur);
        }
      }
      if (q.empty()) tm = a[i].t;
      if (a[i].p == -1) a[i].p = priors[mb];
      q.insert(a[i]);
      if (a[i].p == priors[mb]) a[i].p = -1;
    }
    while (!q.empty()) {
      auto cur = *q.begin();
      q.erase(q.begin());
      ll candel = (ll)cur.s;
      cur.s -= candel;
      tm += candel;
      if (cur.s == 0) {
        ans[cur.i] = tm;
      } else {
        q.insert(cur);
      }
    }
    if (ans[id] <= T) rb = mb;
    else lb = mb;
  }

  ll tm = 0;
  for (int i = 0; i < n; i++) {
    while (tm < a[i].t && !q.empty()) {
      auto cur = *q.begin();
      q.erase(q.begin());
      ll candel = min(a[i].t - tm, (ll)cur.s);
      cur.s -= candel;
      tm += candel;
      if (cur.s == 0) {
        ans[cur.i] = tm;
      } else {
        q.insert(cur);
      }
    }
    if (q.empty()) tm = a[i].t;
    if (a[i].p == -1) a[i].p = priors[rb];
    q.insert(a[i]);
  }
  while (!q.empty()) {
    auto cur = *q.begin();
    q.erase(q.begin());
    ll candel = (ll)cur.s;
    cur.s -= candel;
    tm += candel;
    if (cur.s == 0) {
      ans[cur.i] = tm;
    } else {
      q.insert(cur);
    }
  }

  a[id].p = priors[rb];
  printf("%d\n", a[id].p);
  for (int i = 0; i < n; i++) {
    printf("%lld ", ans[i]);
  }
}
