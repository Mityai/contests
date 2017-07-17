#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("C.in", "w", stdout);
    int n = 1e6, q = 2e6;
    printf("%d %d\n", n, q);

    for (int i = 0; i < q; i++) {
        if (i % 2 == 0) {
            printf("1 1\n");
        } else {
            printf("2\n");
        }
    }
}
