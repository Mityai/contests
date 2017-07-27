#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

#if __APPLE__
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define eprintf(...)
#endif

typedef long long ll;

const vector<int> cnt({6, 2, 5, 5, 4, 5, 6, 3, 7, 6});

/*
 * 0 - 6
 * 1 - 2
 * 2 - 5
 * 3 - 5
 * 4 - 4
 * 5 - 5
 * 6 - 6
 * 7 - 3
 * 8 - 7
 * 9 - 6
 */

int main() {
    int k;
    scanf("%d", &k);

    if (k == 1) {
        puts("-1");
        return 0;
    }

    int len = k / 7 + (k % 7 != 0);
    bool start = len != 1;
    while (len > 0) {
        int d;
        for (d = (start ? 1 : 0); d <= 9; ++d) {
            if (k - cnt[d] <= 7 * (len - 1)) {
                if (k - cnt[d] >= 2 * (len - 1)) {
                    break;
                }
            }
        }
        start = false;
        --len;
        k -= cnt[d];
        printf("%d", d);
    }
    puts("");
}
