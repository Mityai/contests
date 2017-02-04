#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    scanf("%d", &n);

    int a[n];
    for (size_t i = 0; i < n; ++i) {
        scanf("%d", a + i);
    }

    for (size_t i = 0; i < n; ++i) {
        if (i % 2 == (n % 2 == 1 || i < n / 2)) {
            printf("%d ", a[i]);
        } else {
            printf("%d ", a[n - i - 1]);
        }
    }
    puts("");
}
