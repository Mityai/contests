#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

void solve(int n, int m, int s, int d) {
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    sort(a.begin(), a.end());
    
    vector< pair<string, int> > ans;

    int pos = 0;
    for (int cur = 0; cur < n;) {
        if (a[cur] - pos - 1 >= s) {
            int nxt = cur;
            while (nxt + 1 < n && (a[nxt + 1] + 1) - (a[cur] - 1) <= d) {
                if (a[nxt + 1] - a[nxt] - 2 >= s) break;
                nxt++;
            }
            if ((a[nxt] + 1) - (a[cur] - 1) <= d) {
                ans.push_back({"RUN", a[cur] - 1 - pos});
                ans.push_back({"JUMP", (a[nxt] + 1) - (a[cur] - 1)});
                pos = a[nxt] + 1;
                cur = nxt + 1;
            } else {
                puts("IMPOSSIBLE");
                return;
            }
        } else {
            puts("IMPOSSIBLE");
            return;
        }
    }
    if (m - pos > 0) {
        ans.push_back({"RUN", m - pos});
    }

    for (auto pr : ans) {
        printf("%s %d\n", pr.fi.c_str(), pr.se);
    }
}

int main() {
#if __APPLE__
    freopen("D.in", "r", stdin);
    freopen("D.out", "w", stdout);
#endif

    int n, m, s, d;
    while (scanf("%d%d%d%d", &n, &m, &s, &d) == 4) {
        //printf("n = %d m = %d s = %d d = %d\n", n, m, s, d);
        solve(n, m, s, d);
    }
}
