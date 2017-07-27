#include <bits/stdc++.h>
using namespace std;

int main() {
    char s[27], t[27], a[int(1e3) + 1];
    scanf(" %s %s %s", s, t, a);

    char to[27];
    for (int i = 0; i < 26; ++i) {
        to[s[i] - 'a'] = t[i];
    }

    int n = strlen(a);
    for (int i = 0; i < n; ++i) {
        if (isalpha(a[i])) {
            int add = ('A' <= a[i] && a[i] <= 'Z') * ('A' - 'a');
            a[i] = to[tolower(a[i]) - 'a'] + add;
        }
    }

    puts(a);
}
