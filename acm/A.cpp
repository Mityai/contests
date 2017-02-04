#include <bits/stdc++.h>
using namespace std;

bool is_leap(int year) {
    return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
}

int main() {
    int m, n, k;
    scanf("%d%d%d", &m, &n, &k);

    int dd, mm, yy;
    scanf("%d.%d.%d", &dd, &mm, &yy);
}
