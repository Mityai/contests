#include <bits/stdc++.h>
using namespace std;

void parse(const string& s, int& X, int& Y, int& Z) {
    int i_d, i_s = -1;
    for (size_t i = 0; i < s.length(); ++i) {
        if (s[i] == 'd') i_d = i;
        if (s[i] == '+' || s[i] == '-') i_s = i;
    }

    if (i_s == -1) {
        X = stoi(s.substr(0, i_d));
        Y = stoi(s.substr(i_d + 1));
        Z = 0;
    } else {
        X = stoi(s.substr(0, i_d));
        Y = stoi(s.substr(i_d + 1, i_s - i_d));
        Z = stoi(s.substr(i_s));
    }
}

int main() {
    ios_base::sync_with_stdio(false);

    int T;
    cin >> T;

    for (int test = 1; test <= T; ++test) {
        int H, S;
        cin >> H >> S;

        double best = 0.0;
        for (int i = 0; i < S; ++i) {
            string s;
            cin >> s;

            int X, Y, Z;
            parse(s, X, Y, Z);

            const int MAX = Y * X;
            vector<double> prob(MAX + 1);
            prob[0] = 1;
            for (int j = 1; j <= X; ++j) {
                vector<double> cur(MAX + 1);
                for (int k = 1; k <= Y; ++k) {
                    for (int l = 0; l + k <= MAX; ++l) {
                        cur[l + k] += double(prob[l]) / Y;
                    }
                }
                prob.swap(cur);
            }

            double ans = 0.0;
            for (int k = 0; k <= MAX; ++k) {
                if (k + Z >= H) {
                    ans += prob[k];
                }
            }

            best = max(best, ans);
        }

        printf("Case #%d: %.10lf\n", test, best);
    }
}
