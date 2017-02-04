//#include <bits/stdc++.h>
#include <cstdio>
using namespace std;

int ask(int x) {
    printf("%d\n", x);
    fflush(stdout);
    int ret;
    scanf("%d", &ret);
    return ret;
}

int main() {
    int n;
    scanf("%d", &n);

    int l = 1, r = n + 1;
    while (l + 1 < r) {
        int m = (l + r) / 2;
        int f = ask(m);

        if (f == 0) return 0;
        if (f > 0) {
            l = m + 1;
        } else {
            r = m;
        }
    }
    printf("%d\n", l);
    fflush(stdout);
}
