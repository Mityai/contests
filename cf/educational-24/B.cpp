#include <bits/stdc++.h>
#define fi first
#define se secdond
using namespace std;

typedef long long ll;

void no() {
    puts("-1");
    exit(0);
}

int main() {
#if __APPLE__
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif

    int n, m;
    while (scanf("%d%d", &n, &m) == 2) {
        int l[m];
        for (int i = 0; i < m; ++i) {
            scanf("%d", &l[i]);
            --l[i];
        }

        int a[n];
        memset(a, -1, sizeof a);

        set<int> used;
        for (int i = 1; i <= n; ++i) {
            used.insert(i);
        }
        for (int i = 0, cur = l[0]; i + 1 < m; ++i) {
            int nxt = l[i + 1];
            int dist = (nxt - cur + n) % n;
            if (dist == 0) dist = n;
            if (a[cur] != -1 && a[cur] != dist) {
                no();
            } else if (a[cur] == -1) {
                if (used.find(dist) != used.end()) {
                    a[cur] = dist;
                    used.erase(dist);
                } else {
                    no();
                }
            }
            cur = nxt;
        }

        for (int i = 0; i < n; ++i) {
            if (a[i] == -1) {
                a[i] = *used.begin();
                used.erase(used.begin());
            }
        }

        for (int i = 0; i < n; ++i) {
            printf("%d ", a[i]);
        }
        puts("");
    }
}
