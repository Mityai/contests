import java.io.*;
import java.util.*;

public class TestsGen implements Runnable {
    public static void main(String[] args) {
        new Thread(new TestsGen()).start();
    }

    PrintWriter out;

    Random rand = new Random(6439586L);

    static int I = 1;

    static String getName(int i) {
        return "" + i;
    }

    void open() {
        try {
            System.out.println("Generating test " + I);
            out = new PrintWriter(getName(I));
        } catch (FileNotFoundException e) {
            e.printStackTrace();
            System.exit(-1);
        }
    }

    void close() {
        out.close();
        I++;
    }

    final String ALPHA = "abcdefghijklmnopqrstuvwxyz";
    final String ALPHA_EXT = ALPHA + ALPHA.toUpperCase();

    String randString(int len, String alpha) {
        StringBuilder ans = new StringBuilder();
        int k = alpha.length();
        for (int i = 0; i < len; i++) {
            ans.append(alpha.charAt(rand.nextInt(k)));
        }
        return ans.toString();
    }

    long rand(long l, long r) {
        return l + (rand.nextLong() >>> 1) % (r - l + 1);
    }

    int rand(int l, int r) {
        return l + rand.nextInt(r - l + 1);
    }

    final int MAXN = 400000;


    void genTest(int n, int as) {
        open();
        String alph = genAlpha(as);
        out.println(randString(n, alph));
        close();
    }

    private String genAlpha(int as) {
        ArrayList<Character> al = new ArrayList<Character>();
        for (char c : ALPHA.toCharArray()) {
            al.add(c);
        }
        Collections.shuffle(al, rand);
        String alph = "";
        for (int i = 0; i < as; ++i) {
            alph += al.get(i);
        }
        return alph;
    }


    public void solve() throws IOException {
        open();
        out.println("aabaabb");
        close();
        for (int i = 0; i < 10; ++i) {
            genTest(rand(1, 10), rand(1, 5));
            genTest2(rand(1, 10), rand(1, 5));
        }
        for (int i = 0; i < 10; ++i) {
            genTest((i + 1) * (MAXN / 10), rand(1, 26));
            genTest2((i + 1) * (MAXN / 10), rand(1, 26));
        }
        genTest(MAXN, 26);
        genTest2(MAXN, 26);
    }

    private void genTest2(int maxn, int maxc) {
        String s = "";
        String alph = genAlpha(maxc);
        int k = 0;
        while (s.length() < maxn) {
            s += alph.charAt(k);
            k = (k + 1) % maxc;
            int d = 2;
            while (rand.nextBoolean()) d++;
            String ss = "";
            for (int i = 0; i < d; i++) {
                ss += s;
            }
            s = ss;
        }
        s = s.substring(0, maxn);
        open();
        out.println(s);
        close();
    }

    void myAssert(boolean e) {
        if (!e) {
            throw new Error("Assertion failed");
        }
    }

    public void run() {
        try {
            solve();
        } catch (Throwable e) {
            e.printStackTrace();
            System.exit(-1);
        }
    }
}