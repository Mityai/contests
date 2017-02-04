#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#define ll long long
using namespace std;

string palind(string a) {
    string res = "";
    for (int i = 0; i < a.length()/2; i++) {
        res += a[i];
    }
    if (a.length()%2) res += a[a.length()/2];
    for (int i = a.length()/2-1; i >= 0; i--) {
        res += a[i];
    }
    return res;
}

int main() {
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    
    string s;
    cin >> s;
    string p = palind(s);
    if (p > s) {
        cout << p;
    } else {
        int k = s.length()/2-1;
        if(s.length()%2) {
            k++;
        }
        while (s[k] == '9') {
            s[k] = '0';
            k--;
        }
        if (k == -1) {
            cout << 1;
            for (int i = 0; i < s.length()-1; i++) {
                cout << 0;
            }
            cout << 1;
            return 0;
        }
        s[k]++;
        cout << palind(s);
    }

    return 0;
}