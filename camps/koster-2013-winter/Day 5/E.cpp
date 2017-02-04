#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#define ll long long
using namespace std;

const int md = 1000 * 1000 * 1000 + 7;

ll a[10][100];

int main() {
    freopen("phonenumbers.in", "r", stdin);
    freopen("phonenumbers.out", "w", stdout);
    
    int n;
    cin >> n;
    a[0][0] = 0;
    a[1][0] = 1;
    a[2][0] = 1;
    a[3][0] = 1;
    a[4][0] = 1;
    a[5][0] = 1;
    a[6][0] = 1;
    a[7][0] = 1; 
    a[8][0] = 0;
    a[9][0] = 1;
    for (int i = 1; i < n; i++) {
        a[0][i] = a[6][i-1]%md + a[4][i-1]%md;
        a[1][i] = a[8][i-1]%md + a[6][i-1]%md;               
        a[2][i] = a[7][i-1]%md + a[9][i-1]%md;                
        a[3][i] = a[4][i-1]%md + a[8][i-1]%md;                
        a[4][i] = a[3][i-1]%md + a[9][i-1]%md + a[0][i-1]%md;                
        a[5][i] = 0;                
        a[6][i] = a[0][i-1]%md + a[1][i-1]%md + a[7][i-1]%md;                
        a[7][i] = a[6][i-1]%md + a[2][i-1]%md;                
        a[8][i] = a[1][i-1]%md + a[3][i-1]%md;                
        a[9][i] = a[4][i-1]%md + a[2][i-1]%md;                
    }
    ll suml = 0;
    n--;
    for (int i = 0; i < 10; i++) {
        suml += a[i][n]%md;
        suml %= md;
    }
    cout << suml;


    return 0;
}