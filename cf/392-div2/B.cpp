#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

int main() {
#if __APPLE__
    //freopen("B.in", "r", stdin);
    //freopen("B.out", "w", stdout);
#endif

    string s;
    cin >> s;

    map<int, char> pos;
    for (int i = 0; i < s.length(); ++i) {
        if (s[i] != '!') {
            pos[i % 4] = s[i];
        }
    }

    map<char, int> cnt;
    for (int i = 0; i < s.length(); ++i) {
        if (s[i] == '!') {
            ++cnt[pos[i % 4]];
        }
    }

    cout << cnt['R'] << ' ' << cnt['B'] << ' ' << cnt['Y'] << ' ' << cnt['G'] << endl;
}
