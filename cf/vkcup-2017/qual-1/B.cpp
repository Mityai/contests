#include <bits/stdc++.h>
using namespace std;

int main() {
#if __APPLE__
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif

    int n;
    while (scanf("%d", &n) == 1) {
        vector<pair<int, int>> a(n);
        for (int i = 0; i < n; ++i) {
            scanf("%d", &a[i].first);
            a[i].second = i;
        }

        sort(a.begin() + 1, a.end());
        reverse(a.begin() + 1, a.end());

        vector<pair<int, int>> ans;
        int j = 1;
        for (int i = 0; i < j && i < n; ++i) {
            while (a[i].first > 0 && j < n) {
                ans.push_back({a[i].second, a[j].second});
                --a[i].first;
                ++j;
            }
        }

        if (j < n) {
            puts("-1");
        } else {
            printf("%d\n", int(ans.size()));
            for (const auto& p : ans) {
                printf("%d %d\n", p.first + 1, p.second + 1);
            }
        }
    }
}
