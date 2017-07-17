#include <iostream>
#include <vector>
#include <cstdio>
#define fi first
#define se second
using namespace std;

typedef long long ll;

vector<int> get_vector(int x, int len) {
    vector<int> ret;
    while (x > 0) {
        ret.push_back(x % 10);
        x /= 10;
    }
    while (ret.size() < len) {
        ret.push_back(0);
    }
    reverse(ret.begin(), ret.end());
    return ret;
}

int main() {
#if __APPLE__
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
#endif

    int TEST;
    scanf("%d", &TEST);

    for (int test = 1; test <= TEST; ++test) {
        char s[11];
        scanf(" %s", s);

        int len = strlen(s);
        vector<int> x;
        for (int i = 0; i < len; ++i) {
            x.push_back(s[i] - '0');
        }

        int ans = 0;
        for (int n = 1; n < 1e6; ++n) {
            auto v = get_vector(n, len);
            if (v.size() > len) break;
            bool ok = true;
            for (int x : v) {
                if (x > len) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                while (true) {
                    if (v == x) {
                        ++ans;
                        break;
                    }
                    vector<int> b(len);
                    for (int x : v) {
                        if (x > 0) {
                            ++b[x - 1];
                        }
                    }
                    if (v == b) {
                        break;
                    }
                    v.swap(b);
                }
            }
        }

        printf("Case #%d: %d\n", test, ans);
    }
}
