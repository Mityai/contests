#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

vector<pair<int, int>> a, b;

bool cmpa(pair<int, int> f, pair<int, int> g) {
    return f.fi < g.fi || (f.fi == g.fi && b[f.se].fi < b[g.se].fi);
}

bool cmpb(pair<int, int> f, pair<int, int> g) {
    return f.fi < g.fi || (f.fi == g.fi && a[f.se].fi < a[g.se].fi);
}

bool cmpaa(pair<int, int> f, pair<int, int> g) {
    return b[f.se].fi < b[g.se].fi;
}

bool cmpbb(pair<int, int> f, pair<int, int> g) {
    return a[f.se].fi < a[g.se].fi;
}

int main() {
#if __APPLE__
    freopen("D.in", "r", stdin);
    freopen("D.out", "w", stdout);
#endif

    int n;
    scanf("%d", &n);

    a.resize(n);
    b.resize(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i].fi);
        a[i].se = i;
    }
    for (int i = 0; i < n; ++i) {
        scanf("%d", &b[i].fi);
        b[i].se = i;
    }

    sort(a.begin(), a.end(), cmpa);
    sort(b.begin(), b.end(), cmpb);

    vector<int> N(n);
    for (int i = 0; i < n; ++i) N[i] = i;
    set<int> both(N.begin(), N.end());
    vector<pair<int, int>> ina;
    vector<pair<int, int>> inb;
    for (int i = 0; i < n / 2 - (1 - n % 2); ++i) {
        both.erase(a[i].se);
        both.erase(b[i].se);
    }
    for (int i = n / 2 - (1 - n % 2); i < n; ++i) {
        ina.push_back(a[i]);
        inb.push_back(b[i]);
    }

    sort(ina.begin(), ina.end(), cmpaa);
    sort(inb.begin(), inb.end(), cmpbb);

    vector<int> p(both.begin(), both.end());
    p.resize(min(p.size(), size_t(n / 2 + 1)));
    vector<char> used(n, false);
    for (int x : p) {
        used[x] = true;
    }
    while (p.size() < n / 2 + 1) {
        while (!ina.empty() && used[ina.back().se] == true) {
            ina.pop_back();
        }
        if (!ina.empty()) {
            p.push_back(ina.back().se);
            used[ina.back().se] = true;
            ina.pop_back();
        }
        while (!inb.empty() && used[inb.back().se] == true) {
            inb.pop_back();
        }
        if (!inb.empty() && p.size() < n / 2 + 1) {
            p.push_back(inb.back().se);
            used[inb.back().se] = true;
            inb.pop_back();
        }
        if (ina.empty() && inb.empty()) {
            break;
        }
    }

    for (int i = 0; i < n; ++i) {
        if (!used[i] && p.size() < n / 2 + 1) p.push_back(i);
    }

    printf("%d\n", int(p.size()));
    for (int x : p) {
        printf("%d ", x + 1);
    }
    puts("");
}
