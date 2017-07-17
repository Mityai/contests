#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

int main() {
#if __APPLE__
#endif

    string s;
    cin >> s;

    int cnt = 0;
    for (int i = 0; i < s.length() / 2; ++i) {
        if (s[i] != s[s.length() - i - 1]) {
            ++cnt;
        }
    }

    if (cnt == 1 || (cnt == 0 && s.length() % 2 == 1)) {
        puts("YES");
    } else {
        puts("NO");
    }
}
