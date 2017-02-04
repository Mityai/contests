#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#define ll long long
using namespace std;

int a[1000];

int main() {
    freopen("sequence.in", "r", stdin);
    freopen("sequence.out", "w", stdout);
    
    int n;
    cin >> n;
    int d[1000];
    for (int i = 0; i < n; i++) {
        cin >> d[i];
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (d[i] % d[j] == 0) {
                a[i] = max(a[j]+1, a[i]);
            }
            ans = max(ans, a[i]);
        }
    }
    cout << ans+1;

    return 0;
}