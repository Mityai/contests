#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

const int N = 100000 + 5;
bool prime[N + 123];

int main() {
#if __APPLE__
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif

    int n;
    scanf("%d", &n);

    memset(prime, true, sizeof prime);
    prime[0] = prime[1] = false;
    for (int i = 2; i <= n; ++i) {
        if (prime[i]) {
            for (int j = i * i; j <= n + 1; j += i) {
                prime[j] = false;
            }
        }
    }

    if (n <= 2) {
        printf("1\n");
        for (int i = 2; i <= n; ++i) {
            printf("1 ");
        }
        puts("");
    } else {
        printf("%d\n", 2);
        for (int i = 2; i <= n + 1; ++i) {
            if (prime[i]) {
                printf("1 ");
            } else {
                printf("2 ");
            }
        }
        puts("");
    }
}
