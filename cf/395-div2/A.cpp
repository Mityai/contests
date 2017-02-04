#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

int lcm(int a, int b) {
    return a * b / gcd(a, b);
}

int main() {
    int n, m, z;
    cin >> n >> m >> z;
    cout << z / lcm(n, m) << endl;
}
