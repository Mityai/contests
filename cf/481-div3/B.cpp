#include <bits/stdc++.h>
using namespace std;

#if __APPLE__
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define eprintf(...)
#endif

int fin(string& s) {
    for (int i = 0; i + 2 < s.size(); ++i) {
        if (s.substr(i, 3) == "xxx") {
            return i;
        }
    }
    return -1;
}

int main() {
#if __APPLE__
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
#endif

    int n;
    cin >> n;

    string s;
    cin >> s;

    int pos = -1;
    int ans = 0;
    while ((pos = fin(s)) != -1) {
        s.erase(s.begin() + pos);
        ++ans;
    }

    cout << ans << endl;
}
