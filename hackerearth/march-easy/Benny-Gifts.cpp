#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;

    int x = 0, y = 0;
    int ans = 0;
    set< pair<int, int> > q;
    q.insert({x, y});
    for (char c : s) {
        if (c == 'U') y++;
        if (c == 'D') y--;
        if (c == 'L') x--;
        if (c == 'R') x++;
        if (q.count({x, y})) ++ans;
        q.insert({x, y});
    }
    printf("%d\n", ans);
}
