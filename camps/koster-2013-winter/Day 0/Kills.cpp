#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <map>
using namespace std;

struct Player {
	int time;
	int spree;
};

int main() {
    freopen("killer.in", "r", stdin);
    freopen("killer.out", "w", stdout);
//killer.in
    int n;
    cin >> n;
    string s;
    getline(cin, s);
    map<string, Player> m;
    for (int i = 0; i < n; i++) {
    	getline(cin, s);
    	int time_ = ((s[0]-'0')*10 + (s[1]-'0')) * 60 + ((s[3]-'0')*10 + (s[4]-'0'));
    	string name_ = "";
    	time_ += ((s[6]-'0')*10 + (s[7]-'0'))*24*60;
    	for (int j = 17; s[j] != ' '; j++) {
    		name_ += s[j];
    	}
    	int start = 0;
    	string word_ = "";
    	for (int j = 0; j < s.length(); j++) {
    		if (start == 2) {
    			word_ += s[j];
    		}
    		if (s[j] == ':') {
    			start++;
    		}
    	}
    	if (word_ == " Nothing personal") {
	    	if (m[name_].spree == 0) {
	    		m[name_].time = time_;
	    		m[name_].spree++;
	    	} else {
	    		if (time_ - m[name_].time <= 300) {
	    			if (m[name_].spree == 1) cout << "Double kill!" << endl;
	    			else if (m[name_].spree == 2) cout << "Triple kill!" << endl;
	    			else if (m[name_].spree == 3) cout << "Ultra kill!!!" << endl;
	    			else cout << "Rampage!!!" << endl;
	    			m[name_].spree++;
	    		}
	    		m[name_].time = time_;
	    	}
	    }
    }

    return 0;
}