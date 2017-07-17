#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

int oth(int c, int v0, int v1, int a, int l) {
    int p = v0;
    int h = v0;
    int s = 1;
    int cont = 2;
    bool sw = false;
    if (c == v0 || v0 > c) return 1;
    while (!sw) {
        p = v0 + (a * s);
        if (p > v1) p = v1;
        ++s;
        h = (h - l) + p;
        if (h < c) cont++;
        else sw = true;
    }
    return cont;
}

int my(int c, int v0, int v1, int a, int l) {
    int ans = 0;
    while (c > 0) {
        if (ans > 0) {
            c = c + l;
        }
        c -= v0;
        v0 = min(v0 + a, v1);
        ++ans;
    }
    return ans;
}

int main() {
#if __APPLE__
    //freopen("A.in", "r", stdin);
    //freopen("A.out", "w", stdout);
#endif

    for (int c = 1; c <= 55; ++c) {
        for (int l = 0; l <= 55; ++l) {
            for (int v0 = l + 1; v0 <= 55; ++v0) {
                for (int v1 = v0; v1 <= 55; ++v1) {
                    for (int a = 0; a <= 55; ++a) {
                        int o = oth(c, v0, v1, a, l);
                        int m = my(c, v0, v1, a, l);
                        if (o != m) {
                            printf("my = %d, oth = %d\n", m, o);
                            printf("%d %d %d %d %d\n", c, v0, v1, a, l);
                            return 0;
                        }
                    }
                }
            }
        }
    }
}
