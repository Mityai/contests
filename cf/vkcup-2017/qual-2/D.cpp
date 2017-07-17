#include <bits/stdc++.h>
using namespace std;

int get_maxdepth(const string& s) {
    int ret = 0;
    int balance = 0;
    for (char c : s) {
        if (c == '[') {
            ++balance;
        } else {
            --balance;
        }
        ret = max(ret, balance);
    }
    return ret;
}

int get_len(const string& s) {
    int ret = 0;
    for (int i = 0; i < s.length(); ++i, ++ret) {
        if (s[i] == ']' && s[i - 1] == '[') {
            ret += 3;
        }
    }
    return ret;
}

void fill(vector<string>& pic, const string& s, int len, int height) {
    int center = height / 2;
    int balance = 0;
    for (int i = 0, col = 0; i < s.length(); ++i, ++col) {
        if (s[i] == '[') {
            ++balance;
        }
        if (s[i] == ']' && s[i - 1] == '[') {
            col += 3;
        }
        int h = height - 2 * balance;
        int lb = center - h / 2;
        int rb = center + h / 2;
        for (int j = lb; j <= rb; ++j) {
            pic[j][col] = '|';
        }
        pic[lb - 1][col] = pic[rb + 1][col] = '+';
        int d = (s[i] == '[') ? +1 : -1;
        pic[lb - 1][col + d] = pic[rb + 1][col + d] = '-';
        if (s[i] == ']') {
            --balance;
        }
    }
}

void print(const string& s) {
    int maxdepth = get_maxdepth(s);
    int len = get_len(s);
    int height = maxdepth * 2 + 1;
    vector<string> pic(height, string(len, ' '));
    fill(pic, s, len, height);
    for (const string& line : pic) {
        cout << line << endl;
    }
}

int main() {
    int n;
    cin >> n;

    string s;
    cin >> s;

    print(s);
}
