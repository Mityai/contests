import java.util.*;
import java.io.*;

public class crosses_as implements Runnable {
    public void solve() throws IOException {
        Scanner in = new Scanner(new File("crosses.in"));
        PrintWriter out = new PrintWriter("crosses.out");

        int n = in.nextInt();

        int[][][] g = new int[2][2][n + 1];

        g[1][0][1] = 0;
        g[0][1][1] = 0;
        g[1][1][1] = 1;

        g[1][1][2] = 0;
        g[1][0][2] = 0;
        g[0][1][2] = 0;

        for (int i = 3; i <= n; i++) {
            for (int l = 0; l < 2; l++) {
                for (int r = 0; r < 2; r++) {
                    boolean[] u = new boolean[2 * n];
                    for (int k = 0; k < i; k++) {
                        if (k == 0 && l == 0) {
                            u[g[1][r][i - 1]] = true;
                        } else if (k == 1 && l == 0 && (r == 0 || i > 3)) {
                            u[g[0][1][1] ^ g[1][r][i - 2]] = true;
                        } else if (k == i - 1 && r == 0) {
                            u[g[l][1][i - 1]] = true;
                        } else if (k == i - 2 && r == 0 && (l == 0 || i > 3)) {
                            u[g[l][1][i - 2] ^ g[1][0][1]] = true;
                        } else if (1 < k && k < i - 2) {
                            u[g[l][1][k] ^ g[1][r][i - k - 1]] = true;
                        }
                    }

                    g[l][r][i] = -1;
                    for (int j = 0; j < 2 * n; j++) {
                        if (!u[j]) {
                            g[l][r][i] = j;
                            break;
                        }
                    }

                    assert g[l][r][i] != -1;
                }
            }
        }

        if (g[0][0][n] == 0) {
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
        new Thread(new crosses_as()).start();
    }
}