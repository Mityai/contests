#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, sum;
    scanf("%d%d", &n, &sum);

    vector<int> mn(n), mx(n);
    int sum_min = 0, sum_max = 0;
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &mn[i], &mx[i]);
        sum_min += mn[i];
        sum_max += mx[i];
    }

    if (sum_min <= sum && sum <= sum_max) {
        puts("YES");
        int left = sum - sum_min;
        for (int i = 0; i < n; ++i) {
            int add = min(left, mx[i] - mn[i]);
            left -= add;
            printf("%d ", mn[i] + add);
        }
    } else {
        puts("NO");
    }
}
