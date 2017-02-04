#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    int t;
    scanf("%d", &t);

    for (int i = 0; i < t; i++) {
        ll n;
        scanf("%lld", &n);

        for (int i = 0; i < n; i++) {
            int a;
            scanf("%d", &a);
        }

        printf("%lld\n", n * (n - 1) / 2);
    }
}
