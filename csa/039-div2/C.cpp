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

int main() {
    ll s;
    scanf("%lld", &s);

    vector<int> d;
    while (s > 0) {
        d.push_back(s % 10);
        s /= 10;
    }

    vector<int> carry(d.size());
    for (int i = 0; i < carry.size() - 1; ++i) {
        scanf("%d", &carry[i]);
    }
    carry.back() = 0;

    vector<ll> dp(d.size() + 1);
    dp[0] = 1;
    for (int i = 1; i < dp.size(); ++i) {
        for (int x = 0; x <= 9; ++x) {
            for (int y = 0; y <= 9; ++y) {
                int add = 0;
                if (i >= 2 && carry[i - 2]) add = 1;
                int rem = (x + y + add) % 10;
                int car = (x + y + add) >= 10;
                if (car == carry[i - 1] && rem == d[i - 1]) {
                    dp[i] += dp[i - 1];
                }
            }
        }
    }

    printf("%lld\n", dp[d.size()]);
}
