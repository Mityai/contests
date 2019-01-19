#include <bits/stdc++.h>
using namespace std;

bool check(int x) {
    int sum = 0;
    while (x > 0) {
        sum += x % 10;
        if (sum > 10) {
            break;
        }
        x /= 10;
    }
    return sum == 10;
}

int main() {
#if __APPLE__
    // freopen("B.in", "r", stdin);
    // freopem("B.out", "w", stdout);
#endif

    int k;
    scanf("%d", &k);

    int cnt = 0;
    int x = 0;
    while (cnt != k) {
        cnt += check(x);
        ++x;
    }
    printf("%d\n", x - 1);
}
