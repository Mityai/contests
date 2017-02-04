/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2012.07.03
 */

#include <cstdio>
#include <cassert>
#include <algorithm>
#include <iostream>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

int n, k;
long long f[70];
int main()
{
  scanf("%d%d", &n, &k);
  f[n] = 1;
  for (int i = n - 1; i >= 0; i--)
    for (int j = 1; j <= k; j++)
      f[i] += f[i + j];
  cout << f[0] << endl;
  return 0;
}
               