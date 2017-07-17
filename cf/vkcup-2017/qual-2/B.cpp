#include <bits/stdc++.h>

std::mt19937 rng(std::chrono::high_resolution_clock::now().time_since_epoch().count());

std::string solve(const std::string& x) {
    std::string ans = x;
    int best = 0; for (char c : ans) best += c - '0';
    int cursum = 0;
    for (int i = 0; i < x.length(); ++i) {
        if (x[i] >= '1') {
            int cur = cursum + (x[i] - '1') +  9 * (int(x.length()) - i - 1);
            if (best <= cur && !(best == cur && ans == x)) {
                best = cur;
                ans = x.substr(0, i);
                ans += x[i] - 1;
                ans += std::string(x.length() - i - 1, '9');
            }
        }
        cursum += x[i] - '0';
    }

    while (*ans.begin() == '0') ans.erase(ans.begin());

    return ans;
}

std::string stup(const std::string& x) {
    int y = atoi(x.c_str());
    int ret = 1;
    int best = 1;
    for (int i = 1; i <= y; ++i) {
        int t = i;
        int cur = 0;
        while (t > 0) {
            cur += t % 10;
            t /= 10;
        }
        if (cur >= best) {
            best = cur;
            ret = i;
        }
    }
    return std::to_string(ret);
}

int main() {
    for (int i = 1; i <= 1e5; ++i) {
        printf("%d\n", i);
        if (solve(std::to_string(i)) != stup(std::to_string(i))) {
            puts("error");
            return 0;
        }
    }
    for (int i = 0; i < 100; ++i) {
        int x = rng() % int(1e9) + 1;
        printf("%d\n", x);
        if (solve(std::to_string(x)) != stup(std::to_string(x))) {
            puts("error");
            return 0;
        }
    }
}
