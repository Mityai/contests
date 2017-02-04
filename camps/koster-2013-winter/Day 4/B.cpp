#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#define ll long long
using namespace std;

int main() {
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    
    ll n, k;
    cin >> n >> k;
    ll mn = k*(k-1)/2;

    ll left = k, right = n;
    while (left < right) {
        ll mid = (left+right)/2;
        if (mid*(mid+1)/2-mn >= n) {
            right = mid;
        } else {
            left = mid+1;
        }
    }
    cout << right-k+1;

    return 0;
}