#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#define ll long long
using namespace std;

int A[201][10001];

int main() {
    freopen("knapsack.in", "r", stdin);
    freopen("knapsack.out", "w", stdout);
    
    int S, N;
    cin >> S >> N;
    int w[N+1];
    for (int i = 1; i <= N; i++) {
        cin >> w[i];
    }
    int ans = 0;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= S; j++) {
            A[i][j] = A[i-1][j];
            if (j >= w[i] && A[i][j] < A[i-1][j-w[i]] + w[i]) {
                A[i][j] = A[i-1][j-w[i]] + w[i];
            }
            ans = max(A[i][j], ans);
        }
    }
    cout << ans;

    return 0;
}