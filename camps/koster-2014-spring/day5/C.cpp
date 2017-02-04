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
    freopen("prefix.in", "r", stdin);
    freopen("prefix.out", "w", stdout);
    
    string s;
    cin >> s;
    vector<int> p = p_func(s);
    for (int i = 0; i < p.size(); i++) {
        cout << p[i] << ' ';
    }
}