#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
#define ll long long
using namespace std;

int main() {
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    
    ll n, k;
    cin >> n >> k;
    if ((double)n/3 <= k) {
        cout << 0;
        return 0;
    }
    ll left = k+1, right = n;
    while (left < right) {
        ll mid = (left+right)/2;
        if ((n+(mid-k))/(double)3 <= mid) {
            right = mid;
        } else {
            left = mid+1;
        }
    }
    cout << right - k;

    return 0;
}