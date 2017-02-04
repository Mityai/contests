#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#define ll long long
using namespace std;

vector<int> z_func(string s, int k) {
    int n = s.length();
    vector<int> z(n);
    int l = 0, r = 0;
    for (int i = 1; i < z.size(); i++) {
        if (i <= r) {
            z[i] = min(z[i-l], r-i+1);
        }
        while (i < s.length() && s[z[i]] == s[i + z[i]]) {
            ++z[i];
        }
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

int main() {
    freopen("search2.in", "r", stdin);
    freopen("search2.out", "w", stdout);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    string t, s;
    cin >> t >> s;
    s = t + s;
    vector<int> z = z_func(s, (int)t.length());
    vector<int> ans;
    for (int i = (int)t.length(); i < z.size(); i++) {
        if (z[i] >= (int)t.length()) {
            ans.push_back(i + 1 - (int)t.length());
        }
    }
    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << ' ';
    }
}