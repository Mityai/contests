#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#define ll long long
using namespace std;

string island[102];

int main() {
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
     
    int n, m;
    cin >> n >> m;
    for (int i = 1; i < n; i++) {
        island[i] = '.';
        string temp;
        cin >> temp;
        island[i] += temp + '.';
    }
    for (int i = 0; i <= m+1; i++) island[n] += '.';
    int counter = 0;
    int fx = -1, fy = -1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (island[i][j] == '.' && (island[i-1][j] == '#' 
                                     || island[i][j-1] == '#'
                                     || island[i+1][j] == '#'
                                     || island[i][j+1] == '#'
                                     || island[i-1][j-1] == '#'
                                     || island[i-1][j+1] == '#'
                                     || island[i+1][j-1] == '#'
                                     || island[i+1][j+1] == '#')) {
                if (fx == -1 && fy == -1) {
                    fx = j; fy = i;
                }
                island[i][j] = '1';
                counter++;
            }
        }
    }
    island[fy][fx] = '0';
    counter--;
    cout << fy << " " << fx << endl;

    // r - 0
    // d - 1
    // l - 2
    // u - 3
    int last_step = 0;
    while (counter > 0) {
        if (last_step == 0) {
            if (island[fy-1][fx] == '1') {
                fy--;
                last_step = 3;
            } else if (island[fy+1][fx] == '1') {
                fy++;
                last_step = 1;
            } else if (island[fy][fx+1] == '1') {
                fx++;
            } else {
                break;
            }
        } else if (last_step == 1) {
            if (island[fy][fx-1] == '1') {
                fx--;
                last_step = 2;
            } else if (island[fy][fx+1] == '1') {
                fx++;
                last_step = 0;
            } else if (island[fy+1][fx] == '1') {
                fy++;
            } else {
                break;
            }
        } else if (last_step == 2) {
            if (island[fy-1][fx] == '1') {
                fy--;
                last_step = 3;
            } else if (island[fy+1][fx] == '1') {
                fy++;
                last_step = 1;
            } else if (island[fy][fx-1] == '1') {
                fx--;
            } else {
                break;
            }
        } else if (last_step == 3) {
            if (island[fy][fx+1] == '1') {
                fx++;
                last_step = 0;
            } else if (island[fy][fx-1] == '1') {
                fx--;
                last_step = 2;
            } else if (island[fy-1][fx] == '1') {
                fy--;
            } else {
                break;
            }
        }
        island[fy][fx] = '0';
        counter--;
        cout << fy << " " << fx << endl;
    }
    // for (int i = 1; i <= n; i++) {
    //     cout << island[i] << endl;
    // }
    // cout << counter;

 
    return 0;
}