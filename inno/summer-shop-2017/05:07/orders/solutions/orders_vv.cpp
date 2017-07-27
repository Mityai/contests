/**
 * Status: OK, 0.987 sec
 */

#include <cassert>
#include <cstdio>
#include <cstdlib>

#define MAXN 100000
#define MAXK 100000
#define SIZE 500

#ifdef _WIN32
#  define I64 "%I64d"
#else
#  define I64 "%Ld"
#endif

int a[MAXN];
int b[MAXN];
int x[2*SIZE+2];
int p[2*SIZE+2];
int v[2*SIZE+2];
long long s[2*SIZE+2];
char c[MAXK];
int xx[MAXN];
int yy[MAXN];
int rr[MAXN];

int cmp(const void *a, const void *b){
	return (*(int*)a- *(int *)b);
}

long long gcd(long long a, long long b){
	long long c = a%b;
	while (c!=0){
		a = b; b = c; c = a%b;
	}
	return b;
}

int main(){
	assert(freopen("orders.in","rt",stdin));
	assert(freopen("orders.out","wt",stdout));
	int sn = 0;
	int sk = 0;
	while (1){
		int n,k;
		scanf("%d %d\n",&n,&k);
		if (n==0 && k==0) break;
		if (n<0 || k<0) return 1;
		sn+=n; sk+=k;
		if (sn>MAXN || sk>MAXK) return 1;
		for(int i = 0; i<n;i++) a[i] = 0;
		for(int i = 0; i<k;i++){
			scanf("%c %d %d",c+i,xx+i,yy+i);
			if (c[i]=='^') scanf("%d",rr+i);
			scanf("\n");
			xx[i]--; //yy[i];
			if (xx[i]>=yy[i]) return 1;
		}
		int ts = 0;
		while (ts < k){
			int tf;
			if (ts+SIZE > k-1) tf = k;
			else tf = ts+SIZE;
			int cc = 0;
			x[cc++] = 0;
			x[cc++] = n;
			for(int i = 0; i<n;i++) b[i] = a[i];
			for(int i = ts; i<tf; i++){
				x[cc++] = xx[i];
				x[cc++] = yy[i];
			}
			qsort(x,cc,sizeof(int), cmp);
			for(int i = 0; i<cc-1;i++) if (x[i]!=x[i+1])
				qsort(a+x[i],x[i+1]-x[i],sizeof(int),cmp);
			for(int i = 0; i<cc-1;i++) {
				p[i]  = x[i]; v[i] = -1; s[i] = 0;
				for(int j = x[i];j<x[i+1];j++) s[i]+=a[j];
			}
			for(int i = ts; i<tf;i++){
				int l = xx[i];
				for(int j = 0; j<cc;j++){
					if (l==x[j]){
						l = j; break;
					}
				}
				int r = yy[i];
				for(int j = 0; j<cc;j++){
					if (r==x[j]){
						r = j; break;
					}
				}
				if (c[i]=='?'){
					long long ss = 0;
					for(int j = l;j<r;j++) ss+=s[j];
					long long e = x[r]-x[l];
					long long g = gcd(ss,e);
					ss/=g; e/=g;
					if (e==1)
						printf(I64"\n",ss);
					else 
						printf(I64"/"I64"\n",ss,e);
				} else {
					for(int j = l;j<r;j++) if (rr[i]>v[j]){
						s[j]+=((long long)(rr[i]-v[j]))*(long long)(p[j]-x[j]);
						v[j] = rr[i];
						while (p[j]<x[j+1] && a[p[j]]<rr[i]){
							s[j]+=rr[i]-a[p[j]++];
						}
					}
				}
			}
			for(int i = 0; i<cc-1;i++){
				for(int j = x[i]; j<x[i+1];j++){
					if (b[j]>v[i]) a[j] = b[j];
					else a[j] = v[i];
				}
			}
			ts = tf;
		}


	}
	fclose(stdout);
	return 0;
}
