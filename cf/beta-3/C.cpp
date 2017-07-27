#include <bits/stdc++.h>
using namespace std;

const int n = 3;
char s[n][n + 1];

void illegal() {
    puts("illegal");
    exit(0);
}

void win(string s) {
    printf("the %s player won\n", s.c_str());
    exit(0);
}

void step(string s) {
    puts(s.c_str());
    exit(0);
}

void draw() {
    puts("draw");
    exit(0);
}

bool is_win(char c) {
    int cnt = 0;
    bool ok = false;
    for (int i = 0; i < n; ++i) {
        if (s[i][0] == c && s[i][1] == c && s[i][2] == c) ++cnt;
    }
    if (cnt >= 2) illegal();
    ok |= cnt > 0;
    cnt = 0;
    for (int i = 0; i < n; ++i) {
        if (s[0][i] == c && s[1][i] == c && s[2][i] == c) ++cnt;
    }
    ok |= cnt > 0;
    if (cnt >= 2) illegal();
    cnt = 0;
    if (s[0][0] == c && s[1][1] == c && s[2][2] == c) ++cnt;
    if (s[2][0] == c && s[1][1] == c && s[0][2] == c) ++cnt;
    ok |= cnt > 0;
    return ok;
}

int main() {
    for (int i = 0; i < n; ++i) {
        scanf(" %s", s[i]);
    }

    int cntX = 0, cnt0 = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cntX += s[i][j] == 'X';
            cnt0 += s[i][j] == '0';
        }
    }
    if (abs(cntX - cnt0) >= 2) illegal();
    if (cntX == cnt0 - 1) illegal();

    bool winX = is_win('X');
    bool winY = is_win('0');
    if (winX && winY) illegal();
    else if (winX) {
        if (cntX == cnt0 + 1) win("first");
        else illegal();
    } else if (winY) {
        if (cnt0 == cntX) win("second");
        else illegal();
    } else {
        if (cntX + cnt0 == n * n) draw();
        if (cntX == cnt0) step("first");
        if (cntX > cnt0) step("second");
    }
}
