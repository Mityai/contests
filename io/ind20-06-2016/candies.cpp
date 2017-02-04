#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("candies.in", "r", stdin);
    freopen("candies.out", "w", stdout);

    int n;
    while (scanf("%d", &n) == 1) {
        int a[n];
        for (int i = 0; i < n; i++) {
            scanf("%d", a + i);
        }

        int ans = 0;
        map<int, int> q;
        for (int i = 0, j = 0; i < n; i++) {
            q[a[i]]++;
            if (q.size() == 2) {
                ans = max(ans, i - j + 1);
            }
            while (j < i && q.size() > 2) {
                q[a[j]]--;
                if (q[a[j]] == 0) q.erase(a[j]);
                j++;
            }
        }

        printf("%d\n", ans);
    }
}
