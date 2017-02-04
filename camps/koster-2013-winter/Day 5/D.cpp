#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#define ll long long
using namespace std;

int sum[36];

int main() {
    freopen("ones.in", "r", stdin);
    freopen("ones.out", "w", stdout);
    
    int N;
    cin >> N;
    sum[1] = 2;
    sum[2] = 4;
    sum[3] = 7;
    for (int i = 4; i <= N; i++) {
        sum[i] = sum[i-3] + sum[i-2] + sum[i-1];
    }
    cout << sum[N];

    return 0;
}