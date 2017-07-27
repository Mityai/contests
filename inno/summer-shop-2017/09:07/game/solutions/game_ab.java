import java.io.*;
import java.util.*;
import java.math.*;

public class game_ab implements Runnable {
    public static void main(String[] args) {
	new Thread(new game_ab()).start();
    }

    @Override
    public void run() {
	try {
	    br = new BufferedReader(new FileReader("game.in"));
	    out = new PrintWriter("game.out");
	    solve();
	    out.close();
	} catch (Throwable e) {
	    e.printStackTrace();
	    System.exit(-1);
	}
    }

    BufferedReader br;
    StringTokenizer st;
    PrintWriter out;
    boolean eof = true;

    String cnv(String a) {
	return a.equals("") ? "0" : a;
    }

    String nextToken() {
	while (st == null || !st.hasMoreElements()) {
	    try {
		st = new StringTokenizer(br.readLine());
	    } catch (Exception e) {
		eof = true;
		return "";
	    }
	}
	return st.nextToken();
    }

    int nextInt() {
	return Integer.parseInt(cnv(nextToken()));
    }

    double nextDouble() {
	return Double.parseDouble(cnv(nextToken()));
    }
    
    void myAssert(boolean e, String msg) {
	if (!e) {
	    throw new Error(msg);
	}
    }

    final int MAXN = 100000;
    
    private void solve() throws IOException {
	int n = nextInt();
	myAssert(1 <= n && n <= MAXN, "n is out of bounds");
	int m = nextInt();
	myAssert(1 <= m && m <= MAXN, "m is out of bounds");
	int k = nextInt() - 1;
	myAssert(0 <= k && k < n, "k is out of bounds");
	g = new ArrayList[n];
	for (int i = 0; i < n; ++i) {
	    g[i] = new ArrayList<Integer>();
	}
	for (int i = 0; i < m; ++i) {
	    int a = nextInt() - 1;
	    myAssert(0 <= a && a < n, "a[" + i + "] is out of bounds");
	    int b = nextInt() - 1;
	    myAssert(0 <= b && b < n, "b[" + i + "] is out of bounds");
	    g[a].add(b);
	}
	p = new int[n];
	ip = new int[n];
	u = new boolean[n];
	time = 0;
	for (int i = 0; i < n; ++i) {
	    if (!u[i]) topsort(i);
	}
	
	for (int i = 0; i < n; ++i) {
	    for (int j : g[i]) {
		myAssert(ip[i] > ip[j], "Not acyclic!!!");
	    }
	}
	
	boolean[] lose = new boolean[n];
	for (int i = 0; i < n; ++i) {
	    lose[i] = true;
	    for (int j : g[p[i]]) {
		if (lose[ip[j]]) {
		    lose[i] = false;
		    break;
		}
	    }
	}
	if (lose[ip[k]]) {
	    out.println("Second player wins");
	} else {
	    out.println("First player wins");
	}
    }

    private void topsort(int i) {
	u[i] = true;
	for (int j : g[i]) {
	    if (!u[j]) topsort(j);
	}
	p[time] = i;
	ip[i] = time;
	++time;
    }

    boolean[] u;
    int[] p, ip;
    int time;
    ArrayList<Integer>[] g;
    
}
