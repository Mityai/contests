#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

bool prime(int x) {
    for (int i = 2; i < x; ++i) {
        if (x % i == 0) return false;
    }
    return true;
}

int main() {
    int n;
    scanf("%d", &n);

    for (int m = 1; m <= 1000; ++m) {
        if (!prime(m * n + 1)) {
            printf("%d\n", m);
            return 0;
        }
    }
}
