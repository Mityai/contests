#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

const int N = 40000;
const int M = 20000;

void no() {
    puts("NO");
    exit(0);
}

int main() {
#if __APPLE__
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif

    int n;
    cin >> n;

    int y = 0;
    for (int i = 0; i < n; i++) {
        int t;
        string s;
        cin >> t >> s;

        if (s[0] == 'N') {
            if (y == 0) {
                no();
            }
            y = (y + t) % N;
        } else if (s[0] == 'S') {
            if (y == M) {
                no();
            }
            y = ((y - t) % N + N) % N;
        } else if (y == 0 || y == M) {
            no();
        }
    }

    if (y != 0) {
        no();
    }

    puts("YES");
}
