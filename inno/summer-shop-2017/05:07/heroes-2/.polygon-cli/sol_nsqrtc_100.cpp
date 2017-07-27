#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cassert>
#include <ctime>
#include <cstring>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <list>
#include <deque>
#include <queue>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

#define pb push_back
#define mp make_pair
#define fs first
#define sc second

const double pi = acos(-1.0);

const int size = 200 * 1000 + 100;
const int blocksize = 500;

int a[size], b[size], c[size], d[size];
int ans[size];
int startpoint[size];
int startdamage[size];
long long damage[size];
long long delta[size];
int n, m;

int main() {



    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
    	scanf("%d%d", &a[i], &b[i]);
    }
    int maxc = blocksize;
    for (int i = 0; i < m; i++) {
    	scanf("%d%d", &c[i], &d[i]);
    	maxc = max(maxc, d[i]);
    }
    for (int i = 0; i < n; i++)
    	a[i] = min(a[i], maxc);

    for (int i = 0; i < m; i++) {
    	if ((i + 1) % blocksize == 0) {
	   		long long cur = 0;
	   		for (int j = 0; j <= maxc; j++) {
	   			cur += delta[j];
	   			damage[j] += cur;
	   			delta[j] = 0;
	   		}
	   		for (int j = 0; j < n; j++)
	   			if (damage[a[j]] < b[j]) {
	   				startpoint[j] = i;
	   				startdamage[j] = (int) damage[a[j]];
	   			}	
    	}
		for (int j = 1; j <= blocksize; j++)
			damage[j] += ((d[i] + j - 1) / j) * 1ll * c[i];
		int prev = maxc + 1;
		for (int j = 1; j <= blocksize; j++) {
			int cur = (d[i] + j - 1) / j;
			cur = max(cur, blocksize + 1);
			delta[cur] += j * c[i];
			delta[prev] -= j * c[i];

			if (cur == blocksize + 1)
				break;
			else
				prev = cur;
		}		 
    }

    for (int i = 0; i < n; i++) {
    	int cur = startpoint[i];
    	b[i] -= startdamage[i];
    	while (cur < m) {
    		int s1 = (d[cur] + a[i] - 1) / a[i];
    		int s2 = (b[i] + c[cur] - 1) / c[cur];

    		b[i] -= min(s1, s2) * c[cur];
    		
    		if (s1 <= s2)
    			cur++;
    		if (b[i] <= 0)
    			break;
    	}

    	printf("%d\n", cur);
    }

    return 0;
}