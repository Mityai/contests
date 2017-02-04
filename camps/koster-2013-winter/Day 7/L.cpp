#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <string>
#define ll long long
using namespace std;

struct BigInt {
    vector<int> digits;
    void input() {
        string s;
        cin >> s;
        for (ll i = (ll)s.length()-1; i >= 0; i--) {
            digits.push_back(s[i] - '0');
        }
    }
    void output() {
        if (digits.size() == 0) {
            cout << 0;
        } else {
            for (ll i = (ll)digits.size()-1; i >= 0; i--) {
                cout << digits[i];
            }
        }
    }
};

BigInt add(BigInt a, BigInt b) {
    int carry = 0;
    for (size_t i = 0; i < max(a.digits.size(), b.digits.size()) || carry; i++) {
        if (i == a.digits.size())
            a.digits.push_back(0);
        a.digits[i] += carry + (i < b.digits.size() ? b.digits[i] : 0);
        carry = a.digits[i] >= 10;
        if (carry) a.digits[i] -= 10;
    }
    while (a.digits.size() > 1 && a.digits.back() == 0)
        a.digits.pop_back();
    return a;
}

BigInt f[52][52];

int main() {
   freopen("knight2.in", "r", stdin);
   freopen("knight2.out", "w", stdout);
    
    int n, m;
    cin >> n >> m;
    
    f[0][0].digits.push_back(1);
    for (int s = 0; s < n+m; s++) {
        for (int i = 0; i < n; i++) {
            int j = s - i;
            if (j >= 0 && j < m) {
                if (f[i][j].digits.size() >= 1) {
                    if (i-1 >= 0 && j+2 < m) {
                        f[i-1][j+2] = add(f[i][j], f[i-1][j+2]);
                    }
                    if (i+1 < n && j+2 < m) {
                        f[i+1][j+2] = add(f[i][j], f[i+1][j+2]);
                    }
                    if (i+2 < n && j+1 < m) {
                        f[i+2][j+1] = add(f[i][j], f[i+2][j+1]);
                    }
                    if (i+2 >= 0 && j-1 >= 0) {
                        f[i+2][j-1] = add(f[i][j], f[i+2][j-1]);
                    }
                }
            }
        }
    }
    f[--n][--m].output();
    
    return 0;
}