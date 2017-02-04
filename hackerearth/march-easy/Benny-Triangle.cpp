#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    double a, b, p;
    cin >> a >> b >> p;

    double S = a * b / 2;
    double l = 0, r = b;
    for (int i = 0; i < 100; i++) {
        double m = (l + r) / 2;
        double x = b - m;
        double y = x / b * a;
        double s = x * y / 2;
        if (s / S > p / 100.0) {
            l = m;
        } else {
            r = m;
        }
    }
    printf("%.2lf\n", r);
}
