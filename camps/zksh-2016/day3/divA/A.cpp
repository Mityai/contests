#include <bits/stdc++.h>
using namespace std;

const int LOG = 17;
const int N = 1 << LOG;
const double pi = atan2(0, -1);

typedef complex<double> cd;

void FFT(vector<cd> &A, bool invert) {
    for (int i = 1, j = 0; i < N; i++) {
        int b = (N >> 1);
        for (; j >= b; b >>= 1) {
            j -= b;
        }
        j += b;
        if (i < j) {
            swap(A[i], A[j]);
        }
    }
 
    for (int len = 2; len <= N; len <<= 1) {
        double ang = 2 * pi / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < N; i += len) {
            cd w(1);
            for (int j = 0; j < len / 2; j++) {
                cd u = A[i + j];
                cd v = A[i + j + len / 2] * w;
                A[i + j] = u + v;
                A[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }

    if (invert) {
        for (int i = 0; i < N; i++) {
            A[i] /= N;
        }
    }
}

vector<cd> multiply(vector<cd> A, vector<cd> B) {
    FFT(A, 0);
    FFT(B, 0);
    for (int i = 0; i < N; i++) {
        A[i] *= B[i];
    }
    FFT(A, 1);
    return A;
}

int main() {
    vector<cd> A(N), B(N);

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        A[x] += 1;
    }

    int m;
    scanf("%d", &m);

    for (int i = 0; i < m; i++) {
        int x;
        scanf("%d", &x);
        B[x] += 1;
    }

    auto C = multiply(A, B);

    for (int i = 0; i < N; i++) {
        if (C[i].real() >= 1 - 0.1) {
            printf("%d %d\n", i, (int)(C[i].real() + 0.5));
        }
    }
}
