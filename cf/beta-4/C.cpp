#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    map<string, int> cnt;
    for (int i = 0; i < n; ++i) {
        string t;
        if (i == 0) getline(cin, t);
        getline(cin, t);
        cout << (cnt[t]++ == 0 ? "OK" : t + to_string(cnt[t] - 1)) << '\n';
    }
}
