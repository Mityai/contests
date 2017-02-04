#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

int main() {
#if __APPLE__
    freopen("3.in", "r", stdin);
    freopen("3.out", "w", stdout);
#else
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    string name0, name1;
    ll inc0, inc1;
    double mul1;
    cin >> name0 >> inc0 >> name1 >> mul1 >> inc1;
    inc1 *= 1000000;
    mul1 *= 1000000;
    ll lmul1 = ll(mul1);

    if (inc1 < inc0 * lmul1) {
        puts("Power up, Evolve");
    } else if (inc1 > inc0 * lmul1) {
        puts("Evolve, Power up");
    } else {
        puts("Whatever");
    }
}
