import java.util.*;

public class units_moving_as {

    double[][] d;
    boolean[] u;
    int[] p;
    int n;
    double m;

    boolean dfs(int i) {
        u[i] = true;

        for (int j = 0; j < n; j++) {
            if (d[i][j] <= m) {
                if (p[j] == -1 || (!u[p[j]] && dfs(p[j]))) {
                    p[j] = i;
                    return true;
                }
            }
        }
        return false;
    }

    public double bestTime(String[] start, String[] finish) {
        n = start.length;
        int[] xs = new int[n];
        int[] ys = new int[n];
        int[] v = new int[n];
        int[] xt = new int[n];
        int[] yt = new int[n];

        for (int i = 0; i < n; i++) {
            Scanner sc = new Scanner(start[i]);
            xs[i] = sc.nextInt();
            ys[i] = sc.nextInt();
            v[i] = sc.nextInt();
        }
        for (int i = 0; i < n; i++) {
            Scanner sc = new Scanner(finish[i]);
            xt[i] = sc.nextInt();
            yt[i] = sc.nextInt();
        }

        d = new double[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                d[i][j] = Math.hypot(xt[j] - xs[i], yt[j] - ys[i]) / v[i];
            }
        }

        u = new boolean[n];
        p = new int[n];

        double l = 0;
        double r = 10000;
        m = (l + r) / 2;
        while (l != m && r != m && r > 1e-13) {
            boolean ok = true;
            Arrays.fill(p, -1);
            for (int i = 0; i < n; i++) {
                Arrays.fill(u, false);
                if (!dfs(i)) {
                    ok = false;
                    break;
                }
            }

            if (ok) {
                r = m;
            } else {
                l = m;
            }
            m = (l + r) / 2;
        }

        return m;
    }

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = Integer.parseInt(in.nextLine());
        String[] start = new String[n];
        for (int i = 0; i < n; i++) {
            start[i] = in.nextLine();
        }
        String[] finish = new String[n];
        for (int i = 0; i < n; i++) {
            finish[i] = in.nextLine();
        }
        System.out.println(new units_moving_as().bestTime(start, finish));
    }

}
 