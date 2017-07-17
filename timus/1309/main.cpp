#include <iostream>
#include <cstdio>

using namespace std;

#if __APPLE__
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define eprintf(...)
#endif

const int N = 1000;
const int MOD = 9973;

typedef long long ll;

int bp[6][MOD];
int gp[MOD];
bool used[MOD];

inline int g(int x, int y) {
    int add = (y * bp[5][x] + bp[3][x] + 3 * x + 7 * y) % MOD;
    int sub = (bp[5][x] + x * y) % MOD;
    int ret = add - sub;
    if (ret < 0) ret += MOD;
    return ret;
}

inline int readInt() {
    int c = getchar();
    while (c <= 32) c = getchar();
    int ret = 0;
    while ('0' <= c && c <= '9') ret = ret * 10 + c - '0', c = getchar();
    return ret;
}

int main() {
#if __APPLE__
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
    double t = clock();
#endif
    for (int i = 0; i < MOD; ++i) {
        bp[0][i] = 1;
        for (int j = 1; j < 6; ++j) {
            bp[j][i] = (bp[j - 1][i] * i) % MOD;
        }
    }
    int n = readInt();
    int ans = 0;
    int v = n / MOD;
    for (int i = 0; i < v; ++i) {
        if (!used[ans]) {
            gp[ans] = ans;
            for (int j = 1; j < MOD; ++j) {
                gp[ans] = g(j, gp[ans]);
            }
            gp[ans] = g(0, gp[ans]);
            used[ans] = true;
        }
        ans = gp[ans];
    }
    int u = n % MOD;
    for (int i = 1; i <= u; ++i) {
        ans = g(i, ans);
    }
    printf("%d\n", ans);
    eprintf("tm = %.4lf\n", double((clock() - t) / CLOCKS_PER_SEC));
}
