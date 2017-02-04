#include <bits/stdc++.h>
using namespace std; 

int main() {
    int n;
    scanf("%d", &n);

    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int k;
    scanf("%d", &k);

    int cnt = 0;
    for (int l = 0; l < n; l++)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j + k < n; j++) {
            if (a[j] > a[j + k]) swap(a[j], a[j + k]), cnt++;
        }
    }

    for (int i = 1; i < n; i++) {
        if (a[i - 1] > a[i]) {
            puts("-1");
            return 0;
        }
    }
    printf("%d\n", cnt);
}
