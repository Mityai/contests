#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cmath>

typedef long long ll;

using namespace std;

int main() {
    freopen("maxsum.in", "r", stdin);
    freopen("maxsum.out", "w", stdout);

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
    	cin >> a[i];
    }

    int ans = a[0], cursum = 0, minsum = 0;
    for (int i = 0; i < n; i++) {
    	cursum += a[i];
    	ans = max(ans, cursum - minsum);
    	minsum = min(minsum, cursum);
    }

    cout << ans << endl;
}