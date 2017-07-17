#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    string s;
    cin >> s;

    s += "0";

    for (size_t i = 0; i < s.length();) {
        size_t j = s.find("0", i);
        printf("%d", int(j) - int(i));
        i = j + 1;
    }
}
