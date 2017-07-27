#include<string>
#include<deque>
#include<queue>
#include<vector>
#include<algorithm>
#include<iostream>
#include<set>
#include<cmath>
#include<tuple>
#include<chrono>
#include<functional>
#include<random>
#include<unordered_set>
using namespace std;
typedef long long int llint;
#define mp make_pair
#define mt make_tuple
#define pub push_back
#define puf push_front
#define pob pop_back
#define pof pop_front
#define fir first
#define sec second
#define res resize
#define ins insert
#define era erase
const llint mod=1000000007;
const llint big=1e17-10;
const long double pai=3.141592653589793238462643383279;
template <class T,class U>void mineq(T& a,U b){if(a>b){a=b;}}
template <class T,class U>void maxeq(T& a,U b){if(a<b){a=b;}}
int main(void){
	int n,i,j,bmax,bmin=0;cin>>n;bmax=2*n-1;
	vector<int>num(2*n-1);
	for(i=0;i<2*n-1;i++){cin>>num[i];}
	while(bmax-bmin!=1){
		int gen=(bmax+bmin)/2;
		//genは大判定
		int hid=2*n-1,mig=-1;
		bool hiu,miu,ans;
		//左距離、右距離,左が大=true 右が大=1
		for(i=n-1;i<2*n-2;i++){
			bool a=(gen<=num[i]),b=(gen<=num[i+1]);
			if(a!=b){continue;}
			if(a==b){hid=i;hiu=(gen<=num[i]);break;}
		}
		for(i=n-1;i>0;i--){
			if((gen<=num[i])==(gen<=num[i-1])){mig=i;miu=(gen<=num[i]);break;}
		}
		if(hid==2*n-1&&mig==-1){ans=(gen<=num[0]);}
		else if((n-1)-mig<hid-(n-1)){ans=miu;}else{ans=hiu;}
		//cout<<"de"<<ans<<" "<<gen<<" "<<hid<<" "<<mig<<endl;
		if(ans){bmin=gen;}else{bmax=gen;}
		
	}
	cout<<bmin<<endl;
	return 0;
}
