#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("robot.in", "r", stdin);
    freopen("robot.out", "w", stdout);

    int k;
    cin >> k;

    string s;
    cin >> s;

    int n = (int)s.length();

    long long ans = 0;
    for (int i = 0, j = 0; i < n; i++) {
        j = max(i + k, j);
        while (j < n && s[j] == s[j - k]) j++;
        ans += j - i - k;
    }

    cout << ans << endl;
}
