#include <bits/stdc++.h> 
#define fi first
#define se second
using namespace std;

using ll = long long;

int main() {
    int n;
    cin >> n;

    if (n / 14 <= 1) {
        if (n == 21) {
            cout << 1 << endl;
        } else {
            cout << -1 << endl;
        }
    } else {
        int left = n % 14;
        if (2 <= left && left <= 12) {
            cout << n / 14 << endl;
        } else {
            cout << -1 << endl;
        }
    }
}   
