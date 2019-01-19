#include <stdbool.h>
#include <stdio.h>

int main() {
    size_t n;
    scanf("%zu", &n);

    int a[10];
    int min = 100;
    for (size_t i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
        if (min > a[i]) min = a[i];
    }

    bool ok = true;
    for (size_t i = 0; i < n; ++i) {
        a[i] -= min;
        if (a[i] != i) {
            ok = false;
            break;
        }
    }
    if (ok) {
        puts("YES");
        return 0;
    }

    ok = true;
    for (size_t i = 0; i < n; ++i) {
        if (a[i] != n - i - 1) {
            ok = false;
            break;
        }
    }
    if (ok) {
        puts("YES");
        return 0;
    }

    puts("NO");
}
