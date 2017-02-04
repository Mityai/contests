#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

int main() {
	freopen("input.txt", "w", stdout);

    const int N = 50;
    int n = rng() % N + 1;
    printf("%d\n", n);

    for (int i = 0; i < n; i++) {
        if (rng() % 2 == 0) {
            printf("%c ", 'A');
            printf("%d\n", rng() % int(20) - int(10));
        } else {
            printf("%c ", 'Q');
            int l = rng() % (int)20 - 10;
            int r = rng() % (int)20 - 10;
            if (l > r) swap(l, r);
            printf("%d %d\n", l, r);
        }
    }
}
