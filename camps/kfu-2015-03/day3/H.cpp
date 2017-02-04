#include <bits/stdc++.h>
using namespace std;

const int INF = 1234567890;

struct Tarif {
    int c, t, p;
};

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    vector<Tarif> a(n);
    for (int i = 0; i < n; i++) {
        scanf("%d%d%d", &a[i].c, &a[i].t, &a[i].p);
    }

    vector<int> d(m);
    for (int i = 0; i < m; i++) {
        scanf("%d", &d[i]);
    }

    int ans = 0, cost = INF;
    for (int i = 0; i < n; i++) {
        int cur = a[i].c * 100;
        for (int j = 0; j < m; j++) {
            if (d[j] < a[i].t) cur += 0;
            else {
                int k = (d[j] + a[i].t - 1) / a[i].t;
                cur += k * a[i].p;
            }
        }
        if (cur < cost) {
            cost = cur;
            ans = i;
        }
    }

    printf("%d\n", ans + 1);
}
