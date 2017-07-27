#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

const int INF = 1e9;

struct Q {
    int w, h, i;
};

bool cmp(const Q& a, const Q& b) {
    return make_pair(a.w, a.h) < make_pair(b.w, b.h);
}

int main() {
    int n, w, h;
    scanf("%d%d%d", &n, &w, &h);

    vector<Q> a(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &a[i].w, &a[i].h);
        a[i].i = i;
    }

    sort(a.begin(), a.end(), cmp);

    vector<int> d(n);
    vector<int> p(n, -1);
    for (int i = 0; i < n; ++i) {
        if (a[i].w > w && a[i].h > h) d[i] = 1;
        for (int j = i - 1; j >= 0; --j) {
            if (d[j] > 0 && a[i].w > a[j].w && a[i].h > a[j].h) {
                if (d[i] < d[j] + 1) {
                    d[i] = d[j] + 1;
                    p[i] = j;
                }
            }
        }
    }

    int v = -1;
    for (int i = 0; i < n; ++i) {
        if (d[i] > 0 && (v == -1 || d[i] > d[v])) {
            v = i;
        }
    }

    vector<int> ans;
    while (v != -1) {
        ans.push_back(a[v].i);
        v = p[v];
    }

    reverse(ans.begin(), ans.end());
    printf("%d\n", int(ans.size()));
    for (int x : ans) {
        printf("%d ", x + 1);
    }
    puts("");
}
