#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
const int N = 150000;

char s[N + 2];

int main() {
    int t;
    scanf("%d", &t);

    for (int test = 0; test < t; ++test) {
        scanf(" %s", s);
        int n = strlen(s);

        string a(s, s + n);
        int ans = 0;
        unordered_set<int> tolook;
        for (int i = 0; i < n; ++i) tolook.insert(i);
        while (true) {
            unordered_set<int> neww;
            unordered_map<int, char> chang;
            for (int id : tolook) {
                int x = a[id] - '0';
                char cur = a[id];
                auto it = chang.find(id);
                if (it != chang.end()) {
                    cur = it->second;
                }
                for (int i = max(0, id - x); i <= min(n - 1, id + x); ++i) {
                    char oth = a[i];
                    it = chang.find(i);
                    if (it != chang.end()) {
                        oth = it->second;
                    }
                    if (abs(i - id) <= abs(oth - cur) && cur > a[i]) {
                        if (it == chang.end()) {
                            chang[i] = a[i];
                        }
                        a[i] = cur;
                        neww.insert(i);
                    }
                }
            }
            tolook.swap(neww);
            if (tolook.empty()) break;
            ++ans;
        }

        printf("%d\n", ans);
    }
}
