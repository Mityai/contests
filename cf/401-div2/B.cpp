#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    string s, t;
    cin >> n >> s >> t;

    vector<int> cnt1(10), cnt2(10);
    for (char c : s) {
        ++cnt1[c - '0'];
    }
    for (char c : t) {
        ++cnt2[c - '0'];
    }

    int have = 0;
    for (int i = 0; i < 10; ++i) {
        int cur = min(cnt1[i] + have, cnt2[i]);
        have += cnt1[i] - cur;
    }

    int mx = 0;
    int cur = cnt1[0];
    for (int i = 1; i < 10; ++i) {
        int tt = min(cnt2[i], cur);
        mx += tt;
        cur -= tt;
        cur += cnt1[i];
    }

    cout << have << endl << mx << endl;
}
