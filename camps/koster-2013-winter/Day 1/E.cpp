
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

typedef long long ll;

ll reverse(ll a) {
    ll b = 0;
    while (a > 0) {
        b *= 10;
        b += a % 10;
        a /= 10;
    }

    return b;
}

int main() {
    freopen("radar.in", "r", stdin);
    freopen("radar.out", "w", stdout);
    
    ll a;
    cin >> a;
    ll counter = 0;
    while (a != reverse(a)) {
        a += reverse(a);
        counter++;
    }
    cout << counter << " " << a;

    return 0;
}