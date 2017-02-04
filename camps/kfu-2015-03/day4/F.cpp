#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    scanf("%d", &n);

    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    sort(a, a + n);

    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] <= cnt) cnt++;
    }

    puts(cnt == n ? "YES" : "NO");
}
