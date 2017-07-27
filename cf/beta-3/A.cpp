#include <bits/stdc++.h>
using namespace std;

string get_dir(int x1, int y1, int x2, int y2) {
    if (x1 < x2 && y1 < y2) return "RU";
    if (x1 < x2 && y1 > y2) return "RD";
    if (x1 > x2 && y1 < y2) return "LU";
    if (x1 > x2 && y1 > y2) return "LD";
    return "bb";
}

string get_dir2(int x1, int y1, int x2, int y2) {
    if (y1 < y2) return "U";
    if (y1 > y2) return "D";
    if (x1 < x2) return "R";
    if (x1 > x2) return "L";
    return "qq";
}

int main() {
    char c1, c2;
    int y1, y2;
    scanf("%c%d", &c1, &y1);
    scanf(" %c%d", &c2, &y2);
    int x1 = c1 - 'a' + 1, x2 = c2 - 'a' + 1;
    int cnt = min(abs(x1 - x2), abs(y1 - y2));
    int ans = max(abs(x1 - x2), abs(y1 - y2));
    cout << ans << endl;
    string dir = get_dir(x1, y1, x2, y2);
    for (int i = 0; i < cnt; ++i) {
        if (dir == "RU") ++x1, ++y1;
        if (dir == "RD") ++x1, --y1;
        if (dir == "LU") --x1, ++y1;
        if (dir == "LD") --x1, --y1;
        cout << dir << endl;
    }
    dir = get_dir2(x1, y1, x2, y2);
    for (int i = cnt; i < ans; ++i) cout << dir << endl;
}
