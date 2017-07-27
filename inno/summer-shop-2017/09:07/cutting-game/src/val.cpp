#include "testlib.h"

const int MAXN = 1 << 16;
const int MINN = 1;
const int MAXA = 100000;

int main() {
	registerValidation();

	int n = inf.readInt(MINN, MAXN, "n");
	inf.readEoln();

	ensuref((n & (n - 1)) == 0, "Count of cells must be power of two");

	for (int i = 0; i < n; ++i) {
		inf.readInt(-MAXA, MAXA, format("a[%d]", i + 1));
		if (i < n - 1) {
			inf.readSpace();
		}
	}
	inf.readEoln();

	inf.readEof();

	return 0;
}
