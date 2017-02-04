#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#define ll long long
using namespace std;

int main() {
    freopen("knapsack.in", "r", stdin);
    freopen("knapsack.out", "w", stdout);
    
    int n;
    cin >> n;
    vector<ll> s(n);
    vector<ll> sums(n);
    for (int i = 0; i < s.size(); i++) {
        cin >> s[i];
        sums[i] = s[i] + (i ? sums[i-1] : 0);
    }
    vector<ll> c(n);
    vector<ll> sums_c(n);
    for (int i = 0; i < c.size(); i++) {
        cin >> c[i];
        sums_c[i] = c[i] + (i ? sums_c[i-1] : 0);
    }
    int q;
    cin >> q;
    vector<ll> ans(q);
    for (int i = 0; i < q; i++) {
        ll w;
        cin >> w;
        vector<ll>::iterator it = upper_bound(sums.begin(), sums.end(), w)-1;
        int pos = it - sums.begin();
        int k;
        if (pos >= 0) {
            ans[i] += sums_c[pos];
            w -= *it;
            k = pos + 1;
        } else {
            k = 0;
        }
        while (k < n) {
            while (s[k] > w && k < n) {
                k++;
            }
            if (k >= n) {
                break;
            }
            it = upper_bound(sums.begin()+k, sums.end(), w + sums[k-1])-1;
            pos = it - sums.begin();
            if (sums[pos] - sums[k-1] > w) {
                pos--;
            }
            ans[i] += sums_c[pos] - sums_c[k-1];
            w -= sums[pos] - sums[k-1];
            k = pos + 1;
        }
    }
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << ' ';
    }
}