#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;

    int ans = 0;
    for (int i = 0; i < (int)s.length(); i++) {
        char c = s[i];
        bool k1 = ('@' < c);
        int ind = tolower(c) - 'a' + 1;
        bool k2 = ('[' > c);
        bool and1 = (k1 & k2);
        bool k3 = ('`' < c);
        bool k4 = ('{' > c);
        bool and2 = (k3 & k4);
        int times1 = and1 * ind;
        int times2 = and2 * ind;
        int minus = times1 - times2;
        ans += minus;
    }
    cout << ans << endl;
}
