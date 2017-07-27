import java.util.*;
import java.io.*;

public class crosses_gk {
    public static void main(String[] args) throws IOException {
        Scanner scanner = new Scanner(new File("crosses.in"));
        int n = scanner.nextInt() + 4;
        int[] g = new int[n + 1];
        boolean[] u = new boolean[n + 1];

        g[0] = 0;
        g[1] = 0;

        int max = 0;

        for (int i = 2; i <= n; i++) {
            Arrays.fill(u, false);
            for (int j = 2; j < i - 2; j++) {
                u[g[j] ^ g[i - 1 - j]] = true;
            }
            int j = 0;
            while (u[j]) j++;
            g[i] = j;
            if (max < j) max = j;
        }

        PrintWriter w = new PrintWriter("crosses.out");
        w.println(g[n] > 0 ? 1 : 2);
        w.close();
    }
}
