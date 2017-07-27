#include <iostream> 
#include <iosfwd> 
#include <iomanip> 
#include <cstdio> 
#include <cstring> 
#include <cstdlib> 
#include <ctime> 
#include <cmath> 
#include <cassert> 
#include <cctype> 
#include <vector> 
#include <bitset> 
#include <set> 
#include <queue> 
#include <stack> 
#include <map> 
#include <deque> 
#include <algorithm> 
#include <string> 
#include <list> 
#include <iterator> 
#include <sstream> 
#include <complex> 
#include <fstream> 
#include <functional> 
#include <numeric> 
#include <utility> 

using namespace std; 
/*****************************************macros************************************/ 
#define TYPE(m,a) __typeof(a) m = a 
#define FOR(i,a,b) for(TYPE(i,(a)); i < (b); ++i) 
#define DFOR(i,a,b) for(TYPE(i,(a)); i >= (b); --i) 
#define ZFOR(i,N) FOR(i,0,N) 
#define DZFOR(i,N) FOR(i,N,0) 
#define SORT(x) sort((x).begin() , (x).end()) 
#define PB(x) push_back((x)) 
#define FORALL(it,v) for(TYPE(it, (v).begin()); it != (v).end(); ++it) 
#define FORRALL(it,v) for(TYPE(it, (v).rbegin()); it != (v).rend(); ++it) 
#define SIZE(x) x.size() 
/****************************************typedefs**********************************/ 
typedef vector<int> VI; 
typedef vector<string> VS; 
typedef vector<double> VD; 
typedef vector<VI> VVI; 
typedef vector<VD> VVD; 
typedef vector<VS> VVS; 
typedef vector<long long> VL; 
typedef vector<VL> VVL; 
typedef vector<bool> VB; 
typedef vector<VB> VBB; 
vector<string> ex2s(string s, char c){vector<string> vs; string tmp=""; for(int i=0;i<s.length();i++){ 
    if(s[i]==c){vs.PB(tmp); tmp=""; continue;} tmp=tmp+s[i];} if(tmp!="") vs.PB(tmp); return vs;} 
vector<string> vroman; 
bool myfunction(string s1, string s2) 
    { 
        vector<string> vs1; 
        vector<string> vs2; 
        vs1 = ex2s(s1,' '); 
        vs2 = ex2s(s2,' '); 

        if(vs1[0] == vs2[0]) 
            { 
                int v1,v2; 
                for(int i=0;i<50;i++) 
                    { 
                        if(vroman[i] == vs1[1]) 
                            v1 = i; 
                        if(vroman[i] == vs2[1]) 
                            v2 = i; 
                    } 
                if(v1>v2) 
                    return false; 
                else return true; 
            } 
        else { 
                if(vs1[0]>vs2[0]) 
                    return false; 
                else return true; 
            } 
    } 


class KingSort{ 

          public: 
          vector <string> getSortedList(vector <string> stv) { 
                    string roman ="I,II,III,IV,V,VI,VII,VIII,IX,X,XI,XII,XIII,XIV,XV,XVI,XVII,XVIII,XIX,XX,XXI,XXII,XXIII,XXIV,XXV,XXVI,XXVII,XXVIII,XXIX,XXX,XXXI,XXXII,XXXIII,XXXIV,XXXV,XXXVI,XXXVII,XXXVIII,XXXIX,XL,XLI,XLII,XLIII,XLIV,XLV,XLVI,XLVII,XLVIII,XLIX,L";
                    vroman = ex2s(roman, ','); 
                    //cout<<vroman.size(); 

                    sort(stv.begin(),stv.end(),myfunction); 
                    return stv; 
              } 



}; 

int main() {
    int n;
    cin >> n;

    vector<string> a(n);
    getline(cin, a[0]);
    for (int i = 0; i < n; ++i) {
        getline(cin, a[i]);
    }

    KingSort b;
    auto result = b.getSortedList(a);
    for (const auto& s : result) {
        cout << s << endl;
    }
}
