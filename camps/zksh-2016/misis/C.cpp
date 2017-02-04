#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

ll f(ll a, ll b) {
    return b ? f(a ^ b, (a & b) << 1) : a;
}

int main() {

    ll a, b;
    while (cin >> a >> b) {

        cout << b * (b + 1) / 2 - a * (a - 1) / 2 << endl;
    }
}
