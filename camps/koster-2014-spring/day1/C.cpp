#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
using namespace std;

int main() {
    freopen("round.in", "r", stdin);
    freopen("round.out", "w", stdout);
    
    int n, m;
    cin >> n >> m;
    vector<float> a(n);
    float sum = 0;
    for (int i = 0; i < a.size(); i++) {
        cin >> a[i];
        sum += a[i];
    }
    int stable = 0;
    vector<int> ans(n);
    for (int i = 0; i < a.size(); i++) {
        a[i] = a[i] * m / sum;
        ans[i] = int(a[i]);
        stable += int(a[i]);
    }
    for (int i = 0; i < ans.size(); i++) {
        if (a[i] != float(int(a[i]))) {
            if (stable < m) {
                ans[i]++;
                stable++;
            }
        }
    }
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << ' ';
    }
}