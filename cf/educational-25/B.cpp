#include <bits/stdc++.h>
using namespace std;

bool check(const vector<string>& a) {
    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0, cnt = 0; j < a[i].size(); ++j) {
            if (a[i][j] == 'X') ++cnt;
            else cnt = 0;
            if (cnt >= 5) return true;
        }
    }
    for (int j = 0; j < a[0].size(); ++j) {
        for (int i = 0, cnt = 0; i < a.size(); ++i) {
            if (a[i][j] == 'X') ++cnt;
            else cnt = 0;
            if (cnt >= 5) return true;
        }
    }
    for (int s = 0; s < a[0].size() + a.size(); ++s) {
        for (int i = 0, cnt = 0; i < a.size(); ++i) {
            int j = s - i;
            if (0 <= j && j < a[0].size()) {
                if (a[i][j] == 'X') ++cnt;
                else cnt = 0;
                if (cnt >= 5) return true;
            }
        }
    }
    for (int s = -20; s < 20; ++s) {
        for (int i = 0, cnt = 0; i < a.size(); ++i) {
            int j = i - s;
            if (0 <= j && j < a[0].size()) {
                if (a[i][j] == 'X') ++cnt;
                else cnt = 0;
                if (cnt >= 5) return true;
            }
        }
    }
    return false;
}

int main() {
    vector<string> a(10);
    for (int i = 0; i < 10; ++i) cin >> a[i];
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (a[i][j] == '.') {
                a[i][j] = 'X';
                if (check(a)) {
                    puts("YES");
                    return 0;
                }
                a[i][j] = '.';
            }
        }
    }
    puts("NO");
}
