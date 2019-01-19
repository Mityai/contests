#include <bits/stdc++.h>
#define FILENAME "02"
using namespace std;

using ll = long long;

struct A {
    int M, S, P;
};

void solution() {
    int R, B, C;
    scanf("%d%d%d", &R, &B, &C);

    vector<A> a(C);
    for (int i = 0; i < C; ++i) {
        scanf("%d%d%d", &a[i].M, &a[i].S, &a[i].P);
    }

    ll lb = 0, rb = 2e18;
    while (lb + 1 < rb) {
        ll mb = (lb + rb) / 2;
        vector<ll> b;
        for (const auto& x : a) {
            ll cur = min(ll(x.M), (mb - x.P) / x.S);
            cur = max(0ll, cur);
            b.push_back(cur);
        }
        sort(b.rbegin(), b.rend());
        ll cnt = 0;
        for (int i = 0; i < R; ++i) {
            cnt += b[i];
        }
        if (cnt >= B) {
            rb = mb;
        } else {
            lb = mb;
        }
    }

    printf("%lld", rb);
}

void run_solution();

int main() {
#if __APPLE__
    freopen(FILENAME ".in", "r", stdin);
    freopen(FILENAME ".out", "w", stdout);
#endif

    run_solution();
}

void run_solution() {
    int T;
    scanf("%d", &T);

    for (int test = 1; test <= T; ++test) {
        printf("Case #%d: ", test);
        solution();
        putchar('\n');
    }
}
