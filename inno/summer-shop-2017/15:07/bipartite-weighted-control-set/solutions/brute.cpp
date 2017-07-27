#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;
#define N 20010
#define K 220010
#define M 1000001000
int n, l, e[2*K], a[2*K], u[N], p[N];
vector <int> m[N];
queue <int> q;
int dfs(int i, int l, int f)
{
	int j, k, r;
	if(!f || i==l) return f;
	for(r=0; p[i]<m[i].size(); p[i]++)
		if(u[e[j=m[i][p[i]]]]==u[i]+1) { k=dfs(e[j], l, min(f, a[j])); a[j]-=k; a[j^1]+=k; f-=k; r+=k; if(!f) break; }
	return r;
}
bool bfs(int b, int l)
{
	int i, j;
	for(i=0; i<n; u[i]=0, p[i]=0, i++);
	for(q.push(b), u[b]=1; !q.empty(); )
		for(i=q.front(), q.pop(), j=0; j<m[i].size(); j++)
			if(a[m[i][j]] && !u[e[m[i][j]]]) { u[e[m[i][j]]]=u[i]+1; q.push(e[m[i][j]]); }
	return u[l]>0;
}
int mxfl(int b, int e)
{
	int i, f;
	for(f=0; bfs(b, e); f+=dfs(b, e, M));
	return f;
}
void add(int i, int j, int c)
{
	e[l]=j; a[l]=c; m[i].push_back(l++);
	e[l]=i; a[l]=0; m[j].push_back(l++);
}
int main()
{
	int i, j, k;
	scanf("%d%d", &n, &k);
	for(i=0; i<n; scanf("%d", &j), add(2*n, i, j), i++);
	for(i=0; i<n; scanf("%d", &j), add(i+n, 2*n+1, j), i++);
	for(; k--; scanf("%d%d", &i, &j), i--, j--, add(i, n+j, M), add(n+j, i, M));
	n=2*n+2;
	printf("%d\n", mxfl(n-2, n-1));
	return 0;
}