#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("B.in", "w", stdout);
    int n = 5e5;
    printf("%d\n", n);
    for (int i = 0; i < n; ++i) {
        printf("%d %d %d %d\n", i, 0, i + 1, 1);
    }
}
