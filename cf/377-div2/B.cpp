#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

int main() {
    int n, k;
    scanf("%d%d", &n, &k);

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int ans = 0;
    while (true) {
        int ind = -1;
        for (int i = 1; i < n; i++) {
            if (a[i - 1] + a[i] < k) {
                ind = i;
                break;
            }
        }
        if (ind == -1) break;
        else {
            ans += k - a[ind] - a[ind - 1];
            a[ind] += k - a[ind] - a[ind - 1];
        }
    }

    printf("%d\n", ans);
    for (int x : a) {
        printf("%d ", x);
    }
    puts("");
}
