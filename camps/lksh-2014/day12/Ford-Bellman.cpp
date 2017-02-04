#include <iostream>
#include <cstdio>
#include <climits>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <algorithm>
#include <set>

typedef long long ll;

using namespace std;

struct Edge {
    int a, b;
    ll t, f;
};

int main() {
    freopen("time.in", "r", stdin);
    freopen("time.out", "w", stdout);

    int n;
    scanf("%d", &n);

    int A, B;
    scanf("%d%d", &A, &B);

    int k;
    scanf("%d", &k);
    
    vector<Edge> e(k);
    for (int i = 0; i < k; i++) {
        scanf("%d%lld%d%lld", &e[i].a, &e[i].t, &e[i].b, &e[i].f);
    }

    vector<ll> d(n + 1, LLONG_MAX);
    d[A] = 0;
    for (;;) {
        bool out = true;
        for (int j = 0; j < k; j++) {
            if (d[e[j].a] <= e[j].t && d[e[j].b] > e[j].f) {
                d[e[j].b] = e[j].f;
                out = false;
            }
        }
        if (out) {
            break;
        }
    }

    printf("%lld\n", d[B]);
}