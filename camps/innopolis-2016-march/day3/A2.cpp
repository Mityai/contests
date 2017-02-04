//#include <bits/stdc++.h>
#include <cstdio>
using namespace std;

typedef long long ll;

int main() {
    int x;
    ll sum = 0;
    while (scanf("%d", &x) == 1) {
        sum += x;
        printf("%lld\n", sum);
        fflush(stdout);
        if (x == 0) break;
    }
}
