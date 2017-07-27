#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <stdio.h>
#include <cstring>
using namespace std;

const int maxx = 100;

int a[100], x[maxx];
int  m, b, p, k;
vector<int> n;

struct _matrix {
        int q[maxx][maxx];

        int* operator[] (int w) {
                return q[w];
        }
};

_matrix matrix, start;

_matrix operator * (_matrix a, _matrix b) {
        _matrix tmp;
        for (int i = 0; i < k; ++i) {
                for (int j = 0; j < k; ++j) {
                        tmp[i][j] = 0;
                }
        }
        for (int i = 0; i < k; ++i) {
                for (int j = 0; j < k; ++j) {
                        for (int l = 0; l < k; ++l) {
                                tmp[i][j] += (a[i][l] * b[l][j]) % p;
                                tmp[i][j] %= p;
                        }
                }
        }
        return tmp;
}

_matrix operator ^ (_matrix a, int pow) {
        _matrix tmp;
        for (int j = 0; j < k; ++j) {
                for (int i  = 0; i < k; ++i) {
                        tmp[j][i] = 0;
                }
                tmp[j][j] = 1;
        }
        while(pow!= 0) {
                if (pow % 2 != 0) {
                        tmp = (tmp * a);
                        --pow;
                } else {
                        a = (a * a);
                        pow /= 2;
                }
        }
        return tmp;
}

_matrix nul() {
        _matrix t;
        for (int j = 0; j < k; ++j) {
                for (int i  = 0; i < k; ++i) {
                        t[j][i] = 0;
                }
                t[j][j] = 1;
        }
        return t;
}

void dec(char* s) {
        int l = strlen(s);
        for (int i = 0; i < l; ++i) {
                n.push_back(s[i] - '0');
        }
        reverse(n.begin(), n.end());
        int i = 0;
        int carry = 1;
        do {
                if (n[i] > 0) {
                        --n[i];
                        carry = 0;
                } else {
                        n[i] = 9;
                }
                ++i;
        } while (carry == 1);
        if (n.back() == 0) {
                n.pop_back();
        }
        reverse(n.begin(), n.end());
}

_matrix prof() {
        _matrix pr;
        for (int i = 0; i < (k); ++i) {
                for (int j = 0; j < (k); ++j) {
                        pr[i][j] = true;
                }
        }
        for (int i = 0; i < k; ++i) {
                for (int j = i; j < k; ++j) {
                        for (int k = 1; k < m; ++k) {
                                if (((i>>k) & 1) == ((j>>k) & 1) && ((i>>(k-1)) & 1) == ((j>>(k-1)) & 1) &&
                                        ((i>>k) & 1) == ((i>>(k-1)) & 1)) {
                                        pr[i][j] = false;
                                        pr[j][i] = false;
                                }
                        }
                }
        }
        return pr;
}

int main () {
        char s[10000];
        cin >> s;
        dec(s);
        scanf("%d%d", &m, &p);
        k = 1<<m;
        start = nul();
        matrix = prof();

        for (int i = 0; i < n.size(); ++i) {
                start = (start ^ 10);
                int power = n[i];
                start = (start * (matrix ^ power));

        }

        long long ans = 0;
        for (int i = 0; i< k; ++i) {
                for (int j = 0; j < k; ++j) {
                        ans = (ans + start[i][j]) % p;
                }
        }
        cout << ans;

        return 0;
}
