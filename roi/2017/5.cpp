#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 2;

char a[N], b[N];

int main() {
    int q;
    scanf("%d", &q);

    while (q--) {
        scanf(" %s %s", a, b);

        int n = strlen(a);

        bool ok = true;
        vector<pair<int, bool>> cnt;
        cnt.reserve(n);
        for (int i = 0; i < n; ++i) {
            int j = i;
            while (j + 1 < n && b[j + 1] == b[j]) {
                ++j;
            }
            if ((i == 0 || (a[i - 1] != b[i] && a[i - 1] != a[i])) && (j == n - 1 || (a[j + 1] != b[j] && a[j + 1] != a[j]))) {
                cnt.clear();
                int cur = 1;
                for (int k = i + 1; k <= j + 1; ++k) {
                    if (k == j + 1 || a[k] != a[k - 1]) {
                        if (a[k - 1] == b[i]) {
                            while (!cnt.empty()) {
                                if (cnt.back().second == 0) {
                                    cur += cnt.back().first;
                                    cnt.pop_back();
                                } else if (cnt.back().first < cur) {
                                    cur += cnt.back().first;
                                    cnt.pop_back();
                                } else {
                                    break;
                                }
                            }
                            cnt.push_back({cur, 0});
                        } else {
                            if (!cnt.empty() && cnt.back().second == 0 && cnt.back().first > cur) {
                                cur += cnt.back().first;
                                cnt.pop_back();
                                while (!cnt.empty()) {
                                    if (cnt.back().second == 0) {
                                        cur += cnt.back().first;
                                        cnt.pop_back();
                                    } else if (cnt.back().first < cur) {
                                        cur += cnt.back().first;
                                        cnt.pop_back();
                                    } else {
                                        break;
                                    }
                                }
                                cnt.push_back({cur, 0});
                            } else {
                                cnt.push_back({cur, 1});
                            }
                        }
                        cur = 1;
                    } else {
                        ++cur;
                    }
                }
                if (cnt.size() > 1 || cnt.back().second == 1) {
                    ok = false;
                    break;
                }
            } else {
                ok = false;
                break;
            }

            i = j;
        }

        if (!ok) {
            puts("No");
        } else {
            puts("Yes");
        }
    }
}
