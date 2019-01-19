#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 1;

int main() {
    int n, a, b;
    scanf("%d%d%d", &n, &a, &b);
    char c1 = 'a', c2 = 'b';
    int sum = a + b;

    char s[N];
    scanf(" %s", s);

    for (int i = 0; i < n; ++i) {
        if (s[i] == '*') {
            continue;
        } else {
            if (a < b) {
                swap(a, b);
                swap(c1, c2);
            }
            if ((i == 0 || s[i - 1] != c1) && a > 0) {
                s[i] = c1;
                --a;
            } else if (b > 0 && s[i - 1] != c2) {
                s[i] = c2;
                --b;
            }
        }
    }

    printf("%d\n", sum - a - b);
}
