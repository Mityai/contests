#include "testlib.h"

using namespace std;

const int MAXN = 200000;

bool exist[MAXN + 10];
int ptr;

bool isExist(int u) {
    return (1 <= u && u <= ptr && exist[u]);
}

int main(){
    registerValidation();
    int n = inf.readInt(1, MAXN, "n");
    inf.readEoln();
    exist[1] = 1;
    ptr = 1;
    for (int i = 0; i < n; i++) {
        char c = inf.readChar();
        inf.readSpace();
        if (c == '+') {
            int v = inf.readInt();
            if (!isExist(v))
                quitf(_fail,"+ request %d: parent(%d) doesn't exist!", i, v);
            exist[++ptr] = true;
        }
        else if (c == '-') {
            int v = inf.readInt();
            if (!isExist(v))
                quitf(_fail,"- request %d: vertex(%d) doesn't exist!", i, v);
            if (v == 1)
                quitf(_fail,"- request %d: you can't delete the root!", i);
            exist[v] = false;                                                     
        }
        else if (c == '?') {
            int v = inf.readInt();
            if (!isExist(v))
                quitf(_fail,"? request %d: vertex v(%d) doesn't exist!", i, v);
            inf.readSpace();
            int u = inf.readInt();
            if (!isExist(u))
                quitf(_fail,"? request %d: vertex u(%d) doesn't exist!", i, u);
        }
        inf.readEoln();
    }
    inf.readEof();
    return 0;
}