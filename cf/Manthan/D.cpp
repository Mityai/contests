#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    scanf("%d", &n);

    int a[n];
    int zeros = 0;
    set< pair<int, int> > has;
    map<int, int> f;
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        zeros += (a[i] == 0);
        f[a[i]]++;
    }

    int ans = max(2, zeros);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                int x = a[i], y = a[j];
                if (x == 0 && y == 0) break;
                //if (has.count({x, y})) break;
                //has.insert({x, y});
                map<int, int> cnt;
                cnt[x]++, cnt[y]++;
                int cur = 2;
                while (true) {
                    int t = x;
                    x = y;
                    y = y + t;
                    if (++cnt[y] > f[y]) break;
                    cur++;
                }
                ans = max(ans, cur);
            }
        }
    }

    printf("%d\n", ans);
}
