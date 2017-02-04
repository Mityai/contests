#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = int(1e6) + 1;

bool prime[N], win[N];

void pre() {
    memset(prime, true, sizeof prime);
    prime[0] = prime[1] = false;
    for (ll i = 2; i < N; i++) {
        for (ll j = i * i; j < N; j += i) {
            prime[j] = false;
        }
    }

    memset(win, false, sizeof win);
    win[1] = win[4] = true;
    for (int i = 5; i < N; i++) {
        if (!prime[i]) {
            for (int j = 1; j <= 4; j++) {
                if (!prime[i - j]) {
                    win[i] |= (!win[i - j]);
                }
            }
        }
    }
}

int main() {
#if __APPLE__
    freopen("input.txt", "r", stdin);
#endif

    pre();

    int n;
    scanf("%d", &n);

    if (win[n]) {
        puts("1");
    } else {
        puts("2");
    }
}
