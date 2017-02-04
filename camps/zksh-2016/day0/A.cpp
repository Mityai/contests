#include <bits/stdc++.h>
using namespace std;

const int N = 1e6;

int zeros[N + 1];

int cnt(int x) {
    if (x == 0) return 1;
    int ret = 0;
    while (x > 0) {
        ret += (x % 10 == 0);
        x /= 10;
    }
    return ret;
}

int main() {
    for (int i = 0; i <= N; i++) {
        zeros[i] = cnt(i);
        if (i > 0) zeros[i] += zeros[i - 1];
    }

    int t;
    scanf("%d", &t);

    for (int i = 0; i < t; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        int ans = zeros[b];
        if (a > 0) ans -= zeros[a - 1];
        printf("%d\n", ans);
    }
}
