//#include <bits/stdc++.h>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#define fi first
#define se second
using namespace std;

struct Jew {
    double v, w;
    int i;
};

int n, k;
vector<Jew> a, tmp;

bool cmp(Jew x, Jew y) {
    return x.v - x.w > y.v - y.w;
}

inline bool can(double m) {
    for (int i = 0; i < n; i++) {
        a[i].w *= m;
    }
    sort(a.begin(), a.end(), cmp);
    double diff = 0;
    for (int i = 0; i < k; i++) {
        diff += a[i].v - a[i].w;
    }
    a = tmp;
    return diff >= 0;
}

int main() {
    freopen("kbest.in", "r", stdin);
    freopen("kbest.out", "w", stdout);

    scanf("%d%d", &n, &k);

    a.resize(n);
    for (int i = 0; i < n; i++) {
        int v, w;
        scanf("%d%d", &v, &w);
        a[i].v = v;
        a[i].w = w;
        a[i].i = i;
    }
    tmp = a;

    double l = 0, r = 1;
    while (can(r)) r *= 2;
    if (r != 1) l = r / 2;
    for (int ii = 0; ii < 20; ii++) {
        double m = (l + r) / 2;
        if (can(m)) l = m;
        else r = m;
    }

    double m = l;
    for (int i = 0; i < n; i++) {
        a[i].w *= m;
    }
    sort(a.begin(), a.end(), cmp);

    for (int i = 0; i < k; i++) {
        printf("%d\n", a[i].i + 1);
    }
}
