#include <algorithm>
#include <cstdio>
#include <vector>
#include <chrono>
#include <random>

using namespace std;

struct A {
  int l, r, p;
};

struct Seg {
  int x, p, type;
  Seg(int x, int p, int type) : x(x), p(p), type(type) {}
};

double solve(int n, const vector<A>& as) {
  vector<Seg> a;
  for (size_t i = 0; i < n; ++i) {
    a.emplace_back(as[i].l, as[i].p, 0);
    a.emplace_back(as[i].r, as[i].p, 1);
  }

  sort(a.begin(), a.end(), [](const Seg& l, const Seg& r) {
    return l.x < r.x;
  });

  long double ans = 0;
  long double p = 0;
  int half = 0;
  for (int i = 0, prevx = -1; i < a.size();) {
    if (half) {
      ans += (a[i].x - prevx) * 0.5;
    } else {
      ans += (a[i].x - prevx) * p;
    }
    prevx = a[i].x;
    while (i < a.size() && a[i].x == prevx) {
      const long double pp = a[i].p / 100.0;
      if (a[i].type == 0) {
        if (a[i].p == 50) {
          ++half;
        } else {
          p = p * (1 - pp) + (1 - p) * pp;
        }
      } else {
        if (a[i].p == 50) {
          --half;
        } else {
          p = (p - pp) / (1 - 2 * pp);
        }
      }
      ++i;
    }
  }

  return double(ans);
}

double slow(int n, const vector<A>& as) {
  int l = 1e9;
  int r = 0;
  for (auto& a : as) {
    l = min(l, a.l);
    r = max(r, a.r);
  }
  double ans = 0;
  for (++l; l <= r; ++l)  {
    vector<A> curas;
    for (size_t i = 0; i < n; ++i) {
      if (as[i].l < l && l <= as[i].r) {
        curas.push_back(as[i]);
      }
    }
    double p = 0;
    for (unsigned long mask = 0; mask < (1u << curas.size()); ++mask) {
      if (__builtin_popcount(mask) % 2 == 0) {
        continue;
      }
      double curp = 1;
      for (size_t i = 0; i < curas.size(); ++i) {
        double ps = curas[i].p / 100.0;
        if ((mask >> i) & 1) {
          curp *= ps;
        } else {
          curp *= 1 - ps;
        }
      }
      p += curp;
    }
    ans += p;
  }
  return ans;
}

pair<int, vector<A>> gen(int n, int l, int r) {
  mt19937 gen;
  vector<A> as(n);
  for (int i = 0; i < n; ++i) {
    int len = gen() % (r - l + 1);
    as[i].l = l + gen() % (r - l - len);
    as[i].r = as[i].l + len;
    as[i].p = gen() % 101;
  }
  return {n, as};
}

void print(int n, const vector<A>& as, double ans1, double ans2) {
  puts("Test:");
  printf("%d\n", n);
  for (int i = 0; i < n; ++i) {
    printf("%d %d %d\n", as[i].l, as[i].r, as[i].p);
  }
  puts("Results");
  printf("correct = %.10lf, my = %.10lf\n", ans2, ans1);
}

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  for (size_t i = 0; i < 1000000; ++i) {
    int n = 20;
    auto input = gen(n, 999999900, 1000000000);
    const auto ans1 = solve(input.first, input.second);
    const auto ans2 = slow(input.first, input.second);
    if (fabs(ans1 - ans2) > 1e-6) {
      print(input.first, input.second, ans1, ans2);
      return 0;
    }
    fprintf(stderr, "iter %d\n", int(i));
  }
}
