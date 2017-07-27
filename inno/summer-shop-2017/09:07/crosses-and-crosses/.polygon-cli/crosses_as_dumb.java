import java.util.*;
import java.io.*;

public class crosses_as_dumb implements Runnable {
    boolean isAllowed(int x) {
        return Integer.toString(x, 2).indexOf("11") == -1 && Integer.toString(x, 2).indexOf("101") == -1;
    }

    String prepend(String s, int n) {
        for (int i = s.length(); i < n; i++) {
            s = "0" + s;
        }
        return s;
    }

    int[] memo;

    int grundy(int x, int n) {
        if (memo[x] != -1) {
            return memo[x];
        }

        boolean[] g = new boolean[2 * n];
        for (int i = 0; i < n; i++) {
            if ((x & (1 << i)) == 0 && isAllowed(x | (1 << i))) {
                g[grundy(x | (1 << i), n)] = true;
            }
        }

        for (int i = 0; i < n; i++) {
            if (!g[i]) {
                System.out.println(prepend(Integer.toString(x, 2), n) + " " + i);
                return memo[x] = i;
            }
        }
        
        return -1;
    }

    public void solve() throws IOException {
        Scanner in = new Scanner(new File("crosses.in"));
        PrintWriter out = new PrintWriter("crosses.out");

        int n = in.nextInt();
        memo = new int[1 << n];
        Arrays.fill(memo, -1);

        int g = grundy(0, n);
        if (g == 0) {
            out.println(2);
        } else {
            out.println(1);
        }

        in.close();
        out.close();
    }

    public void run() {
        try {
            solve();
        } catch (IOException e) {
        }
    }

    public static void main(String[] arg) {
        new Thread(new crosses_as_dumb()).start();
    }
}