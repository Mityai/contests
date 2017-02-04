#include <bits/stdc++.h>
using namespace std;

int main() {
#if __APPLE__
    freopen("C.in", "r", stdin);
#endif

    int n, m;
    while (scanf("%d%d", &n, &m) == 2) {
        set<int> q;
        for (int i = 0; i < n; i++) {
            int x;
            scanf("%d", &x);
            q.insert(x);
        }

        vector<int> ans;
        for (int i = 1;; i++) {
            if (m < i) break;
            if (q.find(i) == q.end()) {
                ans.push_back(i);
                m -= i;
            }
        }

        printf("%d\n", (int)ans.size());
        for (int x : ans) {
            printf("%d ", x);
        }
        puts("");
    }
}
