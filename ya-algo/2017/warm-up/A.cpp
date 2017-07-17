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

    for (int k = 1; k <= n + 1; ++k) {
        if (n % k != 0) {
            printf("%d\n", k);
            return 0;
        }
    }
}
