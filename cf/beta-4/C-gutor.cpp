#include <iostream>
#include <map>
#include <string>

using namespace std;

int main() {
    cin.tie(0);
    map<string, int> database;
    int n;
    string s;

    cin >> n;
    for (size_t i = 0; i < n; ++i) {
        cin >> s;
        if (!database[s]) {
            database[s] = 1;
            cout << "OK" << '\n';
        } else {
            cout << s << database[s] << '\n';
            ++database[s];
        }
    }
}
