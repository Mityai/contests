#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 1e6 + 1;
const int K = 8;

bool primes[N + 1];

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

int main() {
    memset(primes, true, sizeof primes);
    primes[0] = primes[1] = false;
    for (ll p = 2; p * p <= N; ++p) {
        if (primes[p]) {
            for (ll x = p * p; x <= N; x += p) {
                primes[x] = false;
            }
        }
    }

    int cnt[N + 1];
    memset(cnt, 0, sizeof cnt);

    for (int i = 2; i <= N; ++i) {
        if (primes[i]) {
            for (int j = i; j <= N; j += i) {
                ++cnt[j];
            }
        }
    }

    vector<vector<int>> f(N + 1, vector<int>(K));
    for (int i = 1; i <= N; ++i) {
        for (int j = 0; j < K; ++j) {
            f[i][j] += f[i - 1][j];
        }
        ++f[i][cnt[i]];
    }

    int t;
    scanf("%d", &t);

    for (int i = 0; i < t; ++i) {
        int l, r;
        scanf("%d%d", &l, &r);
        --l;
        vector<int> cur = f[r];
        for (int j = 0; j < K; ++j) cur[j] -= f[l][j];
        int ans = 0;
        for (int j = 0; j < K; ++j) {
            --cur[j];
            for (int u = 0; u < K; ++u) {
                if (cur[j] > 0 && cur[u] > 0) {
                    ans = max(ans, gcd(u, j));
                }
            }
            ++cur[j];
        }
        printf("%d\n", ans);
    }
}
