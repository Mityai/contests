#include <bits/stdc++.h>
using namespace std;

int main() {
    const int n = 6;

    double w[n];
    for (int i = 0; i < n; ++i) {
        cin >> w[i];
    }

    double b[n];
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
    }

    double p = 0;
    double q = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (b[j] < w[i]) {
                p += 1.0 / 36;
            } else if (b[j] > w[i]) {
                q += 1.0 / 36;
            }
        }
    }
    
    printf("%.10lf\n", p / (p + q));
}
