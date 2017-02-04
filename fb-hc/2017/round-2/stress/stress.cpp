#include <bits/stdc++.h>
using namespace std;

string files[] = {"testcr",
				   "main",
				   "slow",
				   "checker"};

int main() {
	for (int i = 0; i < 4; i++) {
		system(("g++ -std=c++11 " + files[i] + ".cpp -o " + files[i]).c_str());
	}
	//freopen("stresslog.txt", "w", stdout);


	for (int i = 1;; i++) {
		cout << "New Test #" << i << endl;
		system("./testcr");
        system("cat input.txt");
		system("./main");
		system("./slow");
		//system("./checker");
		system("sleep 0.5");
        system("diff output.txt output2.txt");
        puts("");
	}
}
