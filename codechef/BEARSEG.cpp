#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    int t;
    scanf("%d", &t);

    for (int it = 0; it < t; ++it) {
        int n, P;
        scanf("%d%d", &n, &P);

        vector<int> a(n + 1);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
        }

        map<int, int> cnt;
        int sum = 0;
        int best = a[1] % P;
        ll cntbest = 0;
        for (int i = 0; i <= n; ++i) {
            sum = (sum + a[i]) % P;

            auto mx = cnt.upper_bound(sum);
            int cur;
            int cntcur;
            if (mx == cnt.end()) {
                cur = sum;
                cntcur = cnt[0];
            } else {
                int an = (sum - mx->first + P) % P;
                if (sum > an) {
                    cur = sum;
                    cntcur = cnt[0];
                } else {
                    cur = an;
                    cntcur = mx->second;
                }
            }

            if (cur == best) {
                cntbest += cntcur;
            } else if (best < cur) {
                best = cur;
                cntbest = cntcur;
            }

            ++cnt[sum];
        }

        printf("%d %lld\n", best, cntbest);
    }
}
