#include <bits/stdc++.h>
using namespace std;

const int LEN = 501;
const int C = 26;

int sumlen = 0;

map<string, bool> ok;
int cnt[C];

bool ask(string s) {
    if (ok.find(s) != ok.end()) return ok[s];
    sumlen += s.length();
    if (sumlen > 1e6) assert(false);
    cout << "? " << s << endl;
    cout.flush();
    string ret;
    cin >> ret;
    ok[s] = (ret == "YES");
    return ok[s];
}

int main() {
    for (int i = 0; i < C; i++) {
        string cur;
        for (int j = 0; j < LEN; j++) {
            cur += char('a' + i);
            if (!ask(cur)) break;
            cnt[i]++;
        }
    }

    int len = 0;
    for (int i = 0; i < C; i++) len += cnt[i];

    string ans = "";
    for (int i = 0; i < len; i++) {
        for (char c = 'a'; c <= 'z'; c++) {
            if (cnt[c - 'a'] > 0) {
                string s = "";
                s += c;
                bool ok = true;
                cnt[c - 'a']--;
                for (char p = 'a'; p <= 'z'; p++) {
                    if (cnt[p - 'a'] > 0) {
                        if (!ask(ans + s + string(cnt[p - 'a'], p))) {
                            ok = false;
                            break;
                        }
                    }
                }
                if (ok) {
                    ans += c;
                    break;
                }
                cnt[c - 'a']++;
            }
        }
    }

    cout << "! " << ans << endl;
    cout.flush();
}
