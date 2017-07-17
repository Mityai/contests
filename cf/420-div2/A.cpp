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

    int a[n][n];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &a[i][j]);
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (a[i][j] != 1) {
                bool ok = false;
                for (int k = 0; k < n; ++k) {
                    for (int l = 0; l < n; ++l) {
                        if (a[i][j] == a[i][k] + a[l][j]) {
                            ok = true;
                            break;
                        }
                    }
                }
                if (!ok) {
                    puts("No");
                    return 0;
                }
            }
        }
    }
    puts("Yes");
}
