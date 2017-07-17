#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);

    int t;
    cin >> t;

    for (int i = 0; i < t; ++i) {
        string s;
        cin >> s;

        int flag = 0;
        for (char c : s) {
            if (c == '0') {
                if (flag == 1) flag = 2;
            } else {
                if (flag == 0) flag = 1;
                else if (flag == 2) {
                    flag = 3;
                }
            }
        }

        if (flag == 3 || flag == 0) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
        }
    }
}
