#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    if (n == 0 && k > 1) {
        puts("No");
        return 0;
    }

    if (k >= 4) {
        cout << "No\n";
    } else if (k == 3) {
        puts("Yes");
        printf("%d %d\n", n + n, -n);
    } else if (k == 2) {
        puts("Yes");
        printf("0 %d\n", n);
    } else if (k == 1) {
        puts("Yes");
        if (n == 0) {
            printf("0 1\n");
        } else {
            printf("%d %d\n", n, -n);
        }
    } else if (k == 0) {
        if (n > 0) {
            puts("Yes");
            puts("-1 -1");
        } else {
            puts("Yes");
            puts("1 1");
        }
    }
}
