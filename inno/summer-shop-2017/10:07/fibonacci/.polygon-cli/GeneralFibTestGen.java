import java.io.*;
import java.util.Random;
import java.util.StringTokenizer;

public class GeneralFibTestGen {
    boolean eof;
    Random rand;

    public static void main(String[] args) throws IOException {
        int k = Integer.parseInt(args[0]);
        long n = Long.parseLong(args[1]);

        new GeneralFibTestGen().run(k, n);
    }

    String next() {
        while (st == null || !st.hasMoreTokens()) {
            try {
                st = new StringTokenizer(br.readLine());
            } catch (Exception e) {
                eof = true;
                return "-1";
            }
        }
        return st.nextToken();
    }

    BufferedReader br;
    StringTokenizer st;
    PrintWriter out;

    int nextInt() {
        return Integer.parseInt(next());
    }

    double nextDouble() {
        return Double.parseDouble(next());
    }

    void run(int k, long n) throws IOException {
        String name = "name";
        InputStream input = System.in;
        OutputStream output = System.out;
        try {
            File f = new File(name + ".in");
            if (f.exists() && f.canRead()) {
                input = new FileInputStream(f);
                output = new FileOutputStream(name + ".out");
            }
        } catch (Exception e) {
        }

        br = new BufferedReader(new InputStreamReader(input));
        out = new PrintWriter(output);

        solve(k, n);

        br.close();
        out.close();
    }

    void solve(int k, long n) {
        rand = new Random(n * 10 + k);
        int max = 1_000_000_000;

        out.println(k + " " + n);
        for (int i = 0; i < k - 1; ++i){
            out.print(rand.nextInt(max) + " ");
        }
        out.println(rand.nextInt(max));

        for (int i = 0; i < k - 1; ++i){
            out.print(rand.nextInt(max) + " ");
        }
        out.println(rand.nextInt(max));
    }
}
