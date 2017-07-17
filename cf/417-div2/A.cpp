#include <bits/stdc++.h>
using namespace std;

int main() {
    int a[4][4];
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            cin >> a[i][j];
        }
    }

    for (int i = 0; i < 4; ++i) {
        if (a[i][3] == 1) {
            int nxt = (i + 1) % 4;
            int prev = (i - 1 + 4) % 4;
            int op = (i + 2) % 4;
            bool bad = false;
            bad |= a[nxt][0];
            bad |= a[op][1];
            bad |= a[prev][2];
            for (int j = 0; j < 3; ++j) {
                bad |= a[i][j];
            }
            if (bad) {
                puts("YES");
                return 0;
            }
        }
    }
    puts("NO");
}
