#include <bits/stdc++.h>
using namespace std;

const int NEED = 50;

int main() {
    int t;
    scanf("%d", &t);

    for (int test = 1; test <= t; ++test) {
        int n;
        scanf("%d", &n);

        vector<int> w(n);
        for (int j = 0; j < n; ++j) {
            scanf("%d", &w[j]);
        }
        sort(w.rbegin(), w.rend());

        int ans = 0;
        for (int i = 0, j = n - 1; i <= j; ++i) {
            int minw = w[i];
            int cnt = 1;
            while (i < j && minw * cnt < NEED) {
                ++cnt;
                --j;
            }
            if (minw * cnt >= NEED) {
                ++ans;
            } else {
                break;
            }
        }

        printf("Case #%d: %d\n", test, ans);
    }
}
