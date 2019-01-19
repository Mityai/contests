#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    string a[3];
    for (int i = 0; i < 3; ++i) cin >> a[i];
    int l = a[0].size();

    vector<pair<int, int>> mxget(3);
    for (int i = 0; i < 3; ++i) {
        map<char, int> cnt;
        for (char c : a[i]) {
            ++cnt[c];
        }
        mxget[i].second = i;
        for (char x = 0; x >= 'A' - 'a'; x += 'A' - 'a')
        for (char c = 'a' + x; c <= 'z' + x; ++c) {
            int num = cnt[c];
            int cur = num + n;
            cur = min(cur, l);
            if (num == l && n == 1) {
                cur = l - 1;
            }
            mxget[i].first = max(mxget[i].first, cur);
        }
    }
    sort(mxget.rbegin(), mxget.rend());
    if (mxget[0].first == mxget[1].first) {
        cout << "Draw" << endl;
    } else {
        switch (mxget[0].second) {
            case 0:
                cout << "Kuro" << endl;
                break;
            case 1:
                cout << "Shiro" << endl;
                break;
            case 2:
                cout << "Katie" << endl;
                break;
        }
    }
}
