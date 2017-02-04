#include <bits/stdc++.h>
using namespace std;
 
int main() {
    freopen("input.txt", "r", stdin);
    freopen("output2.txt", "w", stdout);

    int n;
    scanf("%d", &n);

    set<int> q;
    for (int i = 0; i < n; i++) {
        char c;
        scanf(" %c", &c);

        if (c == 'A') {
            int x;
            scanf("%d", &x);
            if (q.find(x) != q.end()) {
                q.erase(x);
            } else {
                q.insert(x);
            }
        } else {
            int l, r;
            scanf("%d%d", &l, &r);

            auto it = q.lower_bound(l);
            int ans = 0;
            while (it != q.end() && *it <= r) {
                ans = max(ans, *it - l);
                l = *it + 1;
                it++;
            }
            ans = max(ans, r - l + 1);
            printf("%d\n", ans);
        }
    }
}
