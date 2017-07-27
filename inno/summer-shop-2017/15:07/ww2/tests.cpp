#include <bits/stdc++.h>
using namespace std;

const int MIN_N = 1;
const int MAX_N = 1e9;

mt19937 rng(228);

int main() {
    for (int i = 4; i <= 10; ++i) {
        string file = to_string(i + 100) + ".t";
        freopen((file + ".t").c_str(), "w", stdout);

        int t = 10;
        printf("%d\n", t);

        for (int j = 1; j <= 10; ++j) {
            printf("%d %d\n", i, j);
        }

        fclose(stdout);
    }
    /*
    for (int i = 1; i <= 60; ++i) {
        string file = to_string(i + 1);
        freopen((file + ".t").c_str(), "w", stdout);

        int t = 10;
        printf("%d\n", t);

        int m = (i - 1) / 2 + 1;
        vector<pair<int, int>> tests(t);
        if (i & 1) {
            tests[0] = {MIN_N, m};
            tests[1] = {MAX_N, m};
        }
        for (int j = (i & 1) ? 2 : 0; j < t; ++j) {
            int n = rng() % MAX_N + 1;
            tests[j] = {n, m};
        }
        shuffle(tests.begin(), tests.end(), rng);
        for (auto& v : tests) {
            printf("%d %d\n", v.first, v.second);
        }

        fclose(stdout);
    }*/
}
