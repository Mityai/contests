#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

int lcm(int a, int b) {
    return a * b / gcd(a, b);
}

int main() {
    int n;
    cin >> n;

    int m[n], r[n];
    for (int i = 0; i < n; i++) {
        cin >> m[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> r[i];
    }

    int f = m[0];
    for (int i = 1; i < n; i++) {
        f = lcm(f, m[i]);
    }

    int cnt = 0;
    for (int i = 0; i < f; i++) {
        bool ok = false;
        for (int j = 0; j < n; j++) {
            if (i % m[j] == r[j]) {
                 ok = true;
            }
        }
        if (ok) cnt++;
    }

    printf("%.10lf\n", double(cnt) / f);
}
