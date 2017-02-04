#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
 
int main() {
    freopen("baseball.in", "r", stdin);
    freopen("baseball.out", "w", stdout);
    
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    int ans = 0;
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            int dist = a[j] - a[i];
            ans += upper_bound(a.begin(), a.end(), a[j]+2*dist) - 
                   lower_bound(a.begin(), a.end(), a[j]+dist);
        }
    }
    cout << ans;

    return 0;
}