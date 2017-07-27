import java.io.OutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.io.IOException;
import java.util.InputMismatchException;
import java.io.InputStreamReader;
import java.io.Writer;
import java.io.BufferedReader;
import java.io.InputStream;

/**
 * Built using CHelper plug-in
 * Actual solution is at the top
 *
 * @author Niyaz Nigmatullin
 */
public class Main {
    public static void main(String[] args) {
        InputStream inputStream = System.in;
        OutputStream outputStream = System.out;
        FastScanner in = new FastScanner(inputStream);
        FastPrinter out = new FastPrinter(outputStream);
        LeastCommonMultiple solver = new LeastCommonMultiple();
        solver.solve(1, in, out);
        out.close();
    }

    static class LeastCommonMultiple {
        public void solve(int testNumber, FastScanner in, FastPrinter out) {
            long n = in.nextLong();
            int NMOD = 4 * 7 * 9;
            int[][] a = new int[NMOD][NMOD];
            for (int curMod = 0; curMod < NMOD; curMod++) {
                for (int dig = 1; dig < 10; dig++) {
                    int nMod = curMod * 10 + dig;
                    if (dig != 5) {
                        if (nMod % dig != 0) continue;
                    }
                    nMod %= NMOD;
                    a[curMod][nMod]++;
                }
            }
            Matrix m = new Matrix(a);
            m = Matrix.powMod(m, n, 0);
            int ans = 0;
            for (int i = 0; i < NMOD; i++) {
                ans = (ans + m.get(0, i));
            }
            long d = ans;
            if (d < 0) d += 1L << 32;
            out.println(d);
        }

    }

    static class Matrix {
        final int[][] a;
        public final int n;
        public final int m;

        public Matrix(int n, int m) {
            this.n = n;
            this.m = m;
            a = new int[n][m];
        }

        public Matrix(int n) {
            this(n, n);
        }

        public Matrix(int[][] a) {
            n = a.length;
            if (n == 0) {
                throw new AssertionError();
            }
            m = a[0].length;
            this.a = new int[n][];
            for (int i = 0; i < n; i++) {
                if (m != a[i].length) {
                    throw new AssertionError();
                }
                this.a[i] = a[i].clone();
            }
        }

        public int get(int x, int y) {
            return a[x][y];
        }

        public static Matrix getOne(int n) {
            Matrix ret = new Matrix(n);
            for (int i = 0; i < n; i++) {
                ret.a[i][i] = 1;
            }
            return ret;
        }

        public Matrix multiplyMod(Matrix b, int mod) {
            if (m != b.n) {
                throw new AssertionError();
            }
            Matrix ret = new Matrix(n, b.m);
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < b.m; j++) {
                    int d = 0;
                    for (int k = 0; k < m; k++) {
                        d = (d + a[i][k] * b.a[k][j]);
                    }
                    ret.a[i][j] = d;
                }
            }
            return ret;
        }

        public static Matrix powMod(Matrix a, long b, int mod) {
            if (a.n != a.m) {
                throw new AssertionError();
            }
            Matrix ret = getOne(a.n);
            while (b > 0) {
                if ((b & 1) == 1) {
                    ret = ret.multiplyMod(a, mod);
                }
                a = a.multiplyMod(a, mod);
                b >>= 1;
            }
            return ret;
        }

    }

    static class FastScanner extends BufferedReader {
        public FastScanner(InputStream is) {
            super(new InputStreamReader(is));
        }


        public int read() {
            try {
                int ret = super.read();
//            if (isEOF && ret < 0) {
//                throw new InputMismatchException();
//            }
//            isEOF = ret == -1;
                return ret;
            } catch (IOException e) {
                throw new InputMismatchException();
            }
        }

        public String next() {
            StringBuilder sb = new StringBuilder();
            int c = read();
            while (isWhiteSpace(c)) {
                c = read();
            }
            if (c < 0) {
                return null;
            }
            while (c >= 0 && !isWhiteSpace(c)) {
                sb.appendCodePoint(c);
                c = read();
            }
            return sb.toString();
        }

        static boolean isWhiteSpace(int c) {
            return c >= 0 && c <= 32;
        }

        public int nextInt() {
            int c = read();
            while (isWhiteSpace(c)) {
                c = read();
            }
            int sgn = 1;
            if (c == '-') {
                sgn = -1;
                c = read();
            }
            int ret = 0;
            while (c >= 0 && !isWhiteSpace(c)) {
                if (c < '0' || c > '9') {
                    throw new NumberFormatException("digit expected " + (char) c
                            + " found");
                }
                ret = ret * 10 + c - '0';
                c = read();
            }
            return ret * sgn;
        }

        public long nextLong() {
            return Long.parseLong(next());
        }

        public String readLine() {
            try {
                return super.readLine();
            } catch (IOException e) {
                return null;
            }
        }

    }

    static class FastPrinter extends PrintWriter {
        public FastPrinter(OutputStream out) {
            super(out);
        }

        public FastPrinter(Writer out) {
            super(out);
        }

    }
}
