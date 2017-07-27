import java.util.*;
import java.io.*;

public class crosses_gk_win {
    public static void main(String[] args) throws IOException {
        Scanner scanner = new Scanner(new File("crosses.in"));
        int n = scanner.nextInt() + 4;
        int[] g = new int[n + 1];
        int[] m = new int[n + 1];
        boolean[] u = new boolean[n + 1];

        g[0] = 0;
        g[1] = 0;

        for (int i = 2; i <= n; i++) {
            Arrays.fill(u, false);
            for (int j = 2; j < i - 2; j++) {
                int f = g[j] ^ g[i - 1 - j];
                u[f] = true;
                if (f == 0) {
                    m[i] = j;
                }
            }
            int j = 0;
            while (u[j]) j++;
            g[i] = j;
        }

        PrintWriter w = new PrintWriter("crosses.out");
        if (g[n] > 0) {
            w.format("1 %d\n", m[n] - 1);
        } else {
            w.format("2\n");
        }
        w.close();
    }
}
