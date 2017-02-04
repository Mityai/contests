#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

void no() {
    cout << "NO\n";
    exit(0);
}

int main() {
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; ++i) {
        cin >> a[i];        
    }
    for (int i = 0; i < n - 1; ++i) {
        if (a[i] < 0) no();
        if (a[i] & 1) {
            a[i]--;
            a[i + 1]--;
        }
    }
    if (a[n - 1] < 0 || (a[n - 1] & 1)) no();
    cout << "YES\n";
    return 0;    
}
