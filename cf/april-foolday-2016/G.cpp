#include <bits/stdc++.h>
using namespace std;

int main() {
    int F, I, T;
    cin >> F >> I >> T;

    int cnt[I];
    memset(cnt, 0, sizeof cnt);

    for (int i = 0; i < F; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < I; j++) {
            if (s[j] == 'Y') {
                cnt[j]++;
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < I; i++) {
        ans += (cnt[i] >= T);
    }
    cout << ans << endl;
}

// asdas
