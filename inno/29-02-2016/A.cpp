#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);

    int n, a, b;
    scanf("%d%d%d", &n, &a, &b);

    printf("%d\n", min(abs(a - b) - 1, n - abs(a - b) - 1));
}
