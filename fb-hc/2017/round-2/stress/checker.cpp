#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

int main() {

	// Input data
	freopen("input.txt", "r", stdin);
    string test = "", t;
    while (cin >> t) {
        test += t;
        test += "\n";
    }
    fclose(stdin);
	
	// Wrong solution
	freopen("output.txt", "r", stdin);
    string s1 = "";
    while (cin >> t) {
        s1 += t;
        s1 += "\n";
    }
    fclose(stdin);

	// Slow solution
	freopen("output2.txt", "r", stdin);
    string s2 = "";
    while (cin >> t) {
        s2 += t;
        s2 += "\n";
    }
    fclose(stdin);

	// Checker
    /*
	{
        cout << test << endl;
        cout << s1 << " _ " << s2 << endl;
		//freopen("stresslog.txt", "a", stdout);
        if (s1 != s2) {
            cout << "FAIL" << endl;
            cout << test << endl;
            cout << s1 << endl << s2 << endl;
            return 0;
        }
	}*/
}
