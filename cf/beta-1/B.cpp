#include <bits/stdc++.h>
using namespace std;

const int LEN = 100;

string num_to_str(int x) {
    string ret;
    while (x > 0) {
        ret += 'A' + (x - 1) % 26;
        x = (x - 1) / 26;
    }
    reverse(ret.begin(), ret.end());
    return ret;
}

int str_to_num(const string& num) {
    int ret = 0;
    for (char c : num) {
        ret = ret * 26 + c - 'A' + 1;
    }
    return ret;
}

int main() {
    int n;
    scanf("%d", &n);

    char s[LEN];
    for (int i = 0; i < n; ++i) {
        scanf(" %s", s);
        size_t m = strlen(s);
        bool typeRC = false;
        bool was_digit = false;
        for (size_t j = 0; j < m; ++j) {
            if ('0' <= s[j] && s[j] <= '9') {
                was_digit = true;
            } else if (was_digit) {
                typeRC = true;
            }
        }

        if (typeRC) {
            int row, col;
            sscanf(s, "R%dC%d", &row, &col);
            string col_str = num_to_str(col);
            printf("%s%d\n", col_str.c_str(), row);
        } else {
            string col;
            int row = 0;
            for (int j = 0; j < m; ++j) {
                if ('0' <= s[j] && s[j] <= '9') row = row * 10 + s[j] - '0';
                else col += s[j];
            }
            int col_num = str_to_num(col);
            printf("R%dC%d\n", row, col_num);
        }
    }
}
