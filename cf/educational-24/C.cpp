#include <bits/stdc++.h>
#define fi first
#define se secdond
using namespace std;

typedef long long ll;

#if __APPLE__
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define eprintf(...)
#endif

struct Divan {
    int x, y;
    int id;
};

bool cmpl(const Divan& d1, const Divan& d2) {
    return d1.x < d2.x;
}

bool cmpr(const Divan& d1, const Divan& d2) {
    return d1.x > d2.x;
}

bool cmpu(const Divan& d1, const Divan& d2) {
    return d1.y < d2.y;
}

bool cmpd(const Divan& d1, const Divan& d2) {
    return d1.y > d2.y;
}

void solve(int d) {
    int n, m;
    scanf("%d%d", &n, &m);

    vector<Divan> ds(d + d);
    for (int i = 0; i < d; ++i) {
        scanf("%d%d%d%d", &ds[i].x, &ds[i].y, &ds[i + d].x, &ds[i + d].y);
        ds[i].id = i;
        ds[i + d].id = i;
    }

    int cntl, cntr, cntu, cntd;
    scanf("%d%d%d%d", &cntl, &cntr, &cntu, &cntd);

    vector<int> left(d), right(d), up(d), down(d);

    sort(ds.begin(), ds.end(), cmpl);
    vector<char> used(d, false);
    vector<int> pr(d);
    for (int i = 0, cnt = 0, last = 0, lx = -1; i < ds.size(); ++i) {
        if (ds[i].x != lx) {
            lx = ds[i].x;
            cnt += last;
            last = 0;
        }
        int id = ds[i].id;
        if (used[id]) {
            left[id] += cnt - (pr[id] != ds[i].x);
        } else {
            ++last;
            pr[id] = ds[i].x;
            used[id] = true;
        }
    }

    sort(ds.begin(), ds.end(), cmpu);
    used.assign(d, false);
    pr.assign(d, 0);
    for (int i = 0, cnt = 0, last = 0, ly = -1; i < ds.size(); ++i) {
        if (ds[i].y != ly) {
            ly = ds[i].y;
            cnt += last;
            last = 0;
        }
        int id = ds[i].id;
        if (used[id]) {
            up[id] += cnt - (pr[id] != ds[i].y);
        } else {
            ++last;
            pr[id] = ds[i].y;
            used[id] = true;
        }
    }

    sort(ds.begin(), ds.end(), cmpr);
    used.assign(d, false);
    pr.assign(d, 0);
    for (int i = 0, cnt = 0, last = 0, lx = -1; i < ds.size(); ++i) {
        if (ds[i].x != lx) {
            lx = ds[i].x;
            cnt += last;
            last = 0;
        }
        int id = ds[i].id;
        if (used[id]) {
            right[id] += cnt - (pr[id] != ds[i].x);
        } else {
            ++last;
            pr[id] = ds[i].x;
            used[id] = true;
        }
    }

    sort(ds.begin(), ds.end(), cmpd);
    used.assign(d, false);
    pr.assign(d, 0);
    for (int i = 0, cnt = 0, last = 0, ly = -1; i < ds.size(); ++i) {
        if (ds[i].y != ly) {
            ly = ds[i].y;
            cnt += last;
            last = 0;
        }
        int id = ds[i].id;
        if (used[id]) {
            down[id] += cnt - (pr[id] != ds[i].y);
        } else {
            ++last;
            pr[id] = ds[i].y;
            used[id] = true;
        }
    }

    for (int i = 0; i < d; ++i) {
        eprintf("l = %d, r = %d, u = %d, d = %d\n", left[i], right[i], up[i], down[i]);
        if (up[i] == cntu && left[i] == cntl && right[i] == cntr && down[i] == cntd) {
            printf("%d\n", i + 1);
            return;
        }
    }
    puts("-1");
}

int main() {
#if __APPLE__
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif

    int d;
    while (scanf("%d", &d) == 1) {
        eprintf("d = %d\n", d);
        solve(d);
    }
}
