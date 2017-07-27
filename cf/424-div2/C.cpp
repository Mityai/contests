#include <bits/stdc++.h>
using namespace std;

int main() {
    int k, n;
    scanf("%d%d", &k, &n);

    vector<int> a(k);
    for (int i = 0; i < k; ++i) {
        scanf("%d", &a[i]);
    }

    set<int> b;
    for (int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        b.insert(x);
    }

    set<int> start;
    for (int i = 0, sum = 0; i < k; ++i) {
        sum += a[i];
        start.insert(*b.begin() - sum);
    }

    int ans = 0;
    for (int x : start) {
        set<int> has = b;
        for (int i = 0; i < k; ++i) {
            x += a[i];
            has.erase(x);
        }
        if (has.empty()) ++ans;
    }

    printf("%d\n", ans);
}
