#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

int main() {
#if __APPLE__
    //freopen(".in", "r", stdin);
    //freopen(".out", "w", stdout);
#endif

    string s;
    cin >> s;

    map<char, int> cnt;
    for (char c : s) {
        cnt[c]++;
    }

    cnt['a'] /= 2;
    cnt['u'] /= 2;

    string bulba = "Bulbasaur";
    int ans = 1e9;
    for (char c : bulba) {
        ans = min(ans, cnt[c]);
    }

    cout << ans << endl;
}
