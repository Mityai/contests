#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    scanf("%d%d", &n, &k);

    vector<int> r(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &r[i]);
    }

    vector<int> bad(n);
    for (int i = 0; i < k; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        --x, --y;
        if (r[x] > r[y]) {
            ++bad[x];
        } else if (r[y] > r[x]) {
            ++bad[y];
        }
    }

    auto a = r;
    sort(a.begin(), a.end());

    for (int i = 0; i < n; ++i) {
        int cnt = lower_bound(a.begin(), a.end(), r[i]) - a.begin();
        printf("%d ", cnt - bad[i]);
    }
    putchar('\n');
}
