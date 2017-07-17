#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("in", "w", stdout);

    printf("50 50 1000\n");
    for (int i = 0; i < 50; ++i) {
        for (int j = 0; j < 50; ++j) {
            printf("0 ");
        }
        puts("");
    }
    int i = 0, j = 0;
    for (int t = 0; t < 1000; ++t) {
        printf("%d %d %d\n", i + 1, j + 1, 100000);
        j = (j + 1) % 50;
        if (j == 0) ++i;
    }
}
