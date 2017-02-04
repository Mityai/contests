#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#define ll long long
using namespace std;

vector<int> p_func(string s) {
    int n = s.length();
    vector<int> p(n);
    int k = 0;
    for (int i = 1; i < p.size(); i++) {
        while (k > 0 && s[k] != s[i]) {
            k = p[k - 1];
        }
        if (s[k] == s[i]) {
            k++;
        }
        p[i] = k;
    }
    return p;
}
 
int main() {
    freopen("period.in", "r", stdin);
    freopen("period.out", "w", stdout);

    string s;
    cin >> s;
    int n = int(s.length());
    vector<int> p = p_func(s);
    if (p[n-1] % (n - p[n-1]) == 0 && p[n-1] > n - p[n-1])
        cout << n - p[n-1] << endl;
    else 
        cout << n << endl;
}