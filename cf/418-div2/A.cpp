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

    int n, k;
    scanf("%d%d", &n, &k);

    int a[n];
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }

    vector<int> b(k);
    for (int i = 0; i < k; ++i) {
        scanf("%d", &b[i]);
    }

    sort(b.rbegin(), b.rend());

    for (int i = 0, j = 0; i < n; ++i) {
        if (a[i] == 0) {
            a[i] = b[j];
            ++j;
        }
    }

    bool ok = true;
    for (int i = 1; i < n; ++i) {
        if (a[i] <= a[i - 1]) {
            ok = false;
        }
    }

    if (ok) {
        puts("No");
    } else {
        puts("Yes");
    }
}
