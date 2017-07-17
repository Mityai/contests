#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

int main() {
#if __APPLE__
    //freopen("A.in", "r", stdin);
    //freopen("A.out", "w", stdout);
#endif

    int n;
    scanf("%d", &n);

    int a[n], b[n];
    for (int i = 0; i < n; ++i) {
        scanf("%d", a + i);
    }
    for (int i = 0; i < n; ++i) {
        scanf("%d", &b[i]);
    }

    int p[n];
    vector<char> used(n + 1, false);
    for (int i = 0; i < n; ++i) {
        bool ok = true;
        for (int j = i + 1; j < n; ++j) {
            if (used[a[j]]) {
                while (--j > i) used[a[j]] = false;
                ok = false;
                break;
            } else {
                used[a[j]] = true;
                p[j] = a[j];
            }
        }
        if (!ok) {
            p[i] = a[i];
            used[a[i]] = true;
            continue;
        }
        int cur = 0;
        for (int j = 1; j <= n; ++j) {
            if (!used[j]) cur = j;
        }
        p[i] = cur;
        int diff = 0;
        for (int j = 0; j < n; ++j) {
            diff += (p[j] != b[j]);
        }
        ok &= (diff == 1);
        if (ok) {
            for (int i = 0; i < n; ++i) {
                printf("%d ", p[i]);
            }
            puts("");
            return 0;
        } else {
            for (int j = i + 1; j < n; ++j) {
                used[a[j]] = false;
            }
            p[i] = a[i];
            used[a[i]] = true;
        }
    }
}
