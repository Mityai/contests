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

    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &p[i]);
        --p[i];
    }

    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        cnt += x;
    }

    int ans = (cnt % 2 == 0);

    vector<char> used(n, false);
    int comps = 0;
    for (int i = 0; i < n; ++i) {
        if (used[i] == false) {
            ++comps;
            int v = i;
            while (used[v] == false) {
                used[v] = true;
                v = p[v];
            }
        }
    }

    if (comps != 1) {
        ans += comps;
    }
    printf("%d\n", ans);
}
