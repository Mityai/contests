#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

int main() {
#if __APPLE__
    //freopen("A.in", "r", stdin);
    //freopen("A.out", "w", stdout);
#endif

    int n;
    scanf("%d", &n);

    vector<int> a(n);
    set<int> all;
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
        all.insert(a[i]);
    }

    set<int> cur;
    for (int i = 0; i < n; ++i) {
        cur.insert(a[i]);
        while (!cur.empty() && *cur.rbegin() == *all.rbegin()) {
            printf("%d ", *cur.rbegin());
            cur.erase(--cur.end());
            all.erase(--all.end());
        }
        puts("");
    }
}
