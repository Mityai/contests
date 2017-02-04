#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#define ll long long
using namespace std;

ll A[61][61];

int main() {
    freopen("tortoise.in", "r", stdin);
    freopen("tortoise.out", "w", stdout);
    
    int N, M;
    cin >> N >> M;
    A[1][1] = 1;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            if (i != 1 || j != 1)
                A[i][j] = A[i-1][j] + A[i][j-1];
        }
    }
    cout << A[N][M];


    return 0;
}