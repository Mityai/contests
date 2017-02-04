#include <bits/stdc++.h>
using namespace std;

int main() {
    int a, b, c;
    cin >> a >> b >> c;

    for (int x = 0; x * a <= c; x++) {
        if ((c - x * a) % b == 0) {
            puts("Yes");
            return 0;
        }
    }
    puts("No");
}

