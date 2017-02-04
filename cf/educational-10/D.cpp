#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

struct Seg {
    int a, b, i, ans;
};

bool cmpa(Seg sg1, Seg sg2) {
    return sg1.b < sg2.b || (sg1.b == sg2.b && sg1.a > sg2.a);
}

bool cmpi(Seg sg1, Seg sg2) {
    return sg1.i < sg2.i;
}

const int N = 1e6;

int fenw[N];

void add(int pos, int val) {
    for (int i = pos; i < N; i = (i | (i + 1))) {
        fenw[i] += val;
    }
}

int sum(int pos) {
    int ret = 0;
    for (int i = pos; i >= 0; i = (i & (i + 1)) - 1) {
        ret += fenw[i];
    }
    return ret;
}

int main() {
#if __APPLE__
    freopen("D.in", "r", stdin);
    freopen("D.out", "w", stdout);
#endif

    int n;
    scanf("%d", &n);

    map<int, int> to;
    vector<Seg> a(n);
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &a[i].a, &a[i].b);
        to[a[i].a] = 0;
        to[a[i].b] = 0;
        a[i].i = i;
    }

    int C = 0;
    for (auto &it : to) {
        it.se = C++;
    }

    for (int i = 0; i < n; i++) {
        a[i].a = to[a[i].a];
        a[i].b = to[a[i].b];
    }

    sort(a.begin(), a.end(), cmpa);
    for (int i = 0, j = 0; i < C; i++) {
        while (j < (int)a.size() && a[j].b < i) j++;
        while (j < (int)a.size() && a[j].b == i) {
            a[j].ans = sum(N) - sum(a[j].a);
            add(a[j].a, 1);
            j++;
        }
    }

    sort(a.begin(), a.end(), cmpi);

    for (int i = 0; i < n; i++) {
        printf("%d\n", a[i].ans);
    }
}
