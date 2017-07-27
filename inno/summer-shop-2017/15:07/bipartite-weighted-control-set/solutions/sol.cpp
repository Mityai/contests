#pragma comment (linker, "/STACK:100000000")
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
#define N 100100
vector <int> m[2*N];
int a[2*N], n, u[2*N], r1, r2;
void dfs(int i)
{
	int j;
	if(i<n) r1+=a[i];
	else r2+=a[i];
	u[i]=1;
	for(j=0; j<m[i].size(); j++)
		if(!u[m[i][j]]) dfs(m[i][j]);
}
int main()
{
	int i, j, k, r;
	for(scanf("%d%d", &n, &k), i=0; i<2*n; scanf("%d", &a[i]), i++);
	for(; k--; scanf("%d%d", &i, &j), i--, j--, m[i].push_back(n+j), m[n+j].push_back(i));
	for(r=0, i=0; i<2*n; i++)
		if(!u[i]) { r1=0; r2=0; dfs(i); r+=min(r1, r2); }
	printf("%d\n", r);
	return 0;
}