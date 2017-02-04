#include <bits/stdc++.h>
using namespace std;

int main() {
    srand(time(NULL));
    int t = 50;
    printf("%d\n", t);
    for (int i = 0; i < t; ++i) {
        int n = 50;
        int R = 10;
        printf("%d %d\n", n, R);
        for (int j = 0; j < n; ++j) {
            printf("%d %d\n", rand() % 1000000, rand() % 1000000);
        }
    }
}
