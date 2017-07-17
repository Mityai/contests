#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main() {
    int n;
    scanf("%d", &n);

    vector<int> a(n + 2);
    a[0] = -INF;
    a[n + 1] = INF;
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }

    vector<int> pref(n + 2, INF);
    for (int i = 1; i <= n; ++i) {
        pref[i] = pref[i - 1] + 1;
        if (a[i] == 0) {
            pref[i] = 0;
        }
    }

    vector<int> next(n + 2, INF);
    for (int i = n; i >= 1; --i) {
        next[i] = next[i + 1] + 1;
        if (a[i] == 0) {
            next[i] = 0;
        }
    }

    for (int i = 1; i <= n; ++i) {
        printf("%d ", min(pref[i], next[i]));
    }
    puts("");
}
