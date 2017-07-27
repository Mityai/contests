#include <iostream>
#include <vector>
#include <set>
#include <cstdio>
#include <map>
#include <cmath>
#include <algorithm>
#include <string.h>
using namespace std;
 
#define MOD 1000000007
 
class Matrix
{
    public:
    int a[30][30];
    int n;
 
    Matrix(int _n)
    {
        n = _n;
        memset(a, 0, sizeof(a));
    }
 
};
 
Matrix mult(Matrix a, Matrix b)
{
    int n = a.n;
    Matrix c(n);
 
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            for (int k = 0; k < n; ++k)
            {
                c.a[i][j] = (c.a[i][j] + 1LL * a.a[i][k] * b.a[k][j]) % MOD;
            }
        }
    }
 
    return c;
}
 
Matrix pow(Matrix a, int pow)
{
    --pow;
    if (!pow) return a;
    Matrix r = a, t = a;
 
    while (pow)
    {
        if (pow & 1) r = mult(r, t);
        t = mult(t, t);
        pow >>= 1;
    }
    return r;
}
 
int main()
{
    cin.sync_with_stdio(0);
    cout.setf(ios::floatfield, ios::fixed);
    cout.precision(8);
 
    int t;
    cin >> t;
    while (t--)
    {
 
        int n, m;
        cin >> n >> m;
 
        Matrix odd(m), even(m);
        for (int i = 0; i < m; ++i)
        {
            if (i) even.a[i][i - 1] = 1;
            if (i + 1 < m) even.a[i][i + 1] = 1;
 
            if (i) odd.a[i][i - 1] = 1;
            odd.a[i][i] = 1;
            if (i + 1 < m) odd.a[i][i + 1] = 1;
        }
 
        if (n > 1)
        {
            even = pow(even, n / 2);
            if (n > 2)
            {
                odd = pow(odd, (n - 1) / 2);
                even = mult(even, odd);
            }
 
            int res = 0;
            for (int i = 0; i < m; ++i)
            {
                for (int j = 0; j < m; ++j)
                {
                    res = (res + even.a[i][j]) % MOD;
                }
            }
 
            cout << res << endl;
        }
        else cout << m << endl;
    }
 
    return 0;
}
