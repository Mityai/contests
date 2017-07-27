import java.io.*;
import java.util.*;

public class array2_as implements Runnable {
    final int MAXC = 256;

    final int MAXLEN = 400000;
    Random rand = new Random();
    
    public void solve() throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("array.in"));
        PrintWriter out = new PrintWriter("array.out");

        String s = in.readLine() + (char)0;
        
        int n = s.length();

        int[] c = new int[n];
        int[] c1 = new int[n];
        for (int i = 0; i < n; i++) {
            c[i] = s.charAt(i);
        }

        
        int[] cnt = new int[MAXC];
        for (int i = 0; i < n; i++) {
            cnt[c[i]]++;
        }
        int[] h = new int[Math.max(MAXC, n)];
        int[] h1 = new int[Math.max(MAXC, n)];
        for (int i = 1; i < MAXC; i++) {
            h[i] = h[i - 1] + cnt[i - 1];
            h1[i] = h[i];
        }

        int[] a = new int[n];
        int[] a1 = new int[n];
        for (int i = 0; i < n; i++) {
            a[h1[c[i]]++] = i;
        }

        int l = 1;
        while (l < n) {
            for (int i = 0; i < n; i++) {               
                int j = ((a[i] - l) % n + n) % n;
                a1[h[c[j]]++] = j;
            }
            int nc = 0;
            h[nc++] = 0;
            for (int i = 1; i < n; i++) {
                if (c[a1[i]] != c[a1[i - 1]] || c[(a1[i] + l) % n] != c[(a1[i - 1] + l) % n]) {
                    h[nc++] = i;
                }
                c1[a1[i]] = nc - 1;
            }

            l *= 2;
            int[] tmp = a; a = a1; a1 = tmp;
            tmp = c; c = c1; c1 = tmp;
        }

        for (int i = 1; i < n; i++) {
            out.print((a[i] + 1) + " ");
        }
        out.println();

        int[] p = new int[n];
        for (int i = 0; i < n; i++) {
            p[a[i]] = i;
        }
        int[] lcp = new int[n - 1];
        int cur = 0;
        for (int i = 0; i < n - 1; i++) {
            cur = Math.max(cur - 1, 0);
            while (s.charAt(i + cur) == s.charAt(a[p[i] - 1] + cur)) {
                cur++;
            }
            lcp[p[i] - 1] = cur;            
        }
        for (int i = 1; i < n - 1; i++) {
            out.print(lcp[i] + " ");
        }
        out.println();

        in.close();
        out.close();
    }

    @Override
    public void run() {
        try {
            solve();
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(1);
        }
    }

    public static void main(String[] s) {
        Locale.setDefault(Locale.US);
        new Thread(new array2_as()).start();
    }
}