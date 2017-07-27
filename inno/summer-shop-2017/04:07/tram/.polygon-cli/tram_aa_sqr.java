// ������ "�������"
// ������� �������������� ��������-��������� ������ 2009-2010.
// ����� ������: �������� ��������, ulyantsev@rain.ifmo.ru
// ����� �������: ����� ���, akhi@rain.ifmo.ru

import java.io.*;
import java.util.*;
import java.math.*;

public class tram_aa_sqr {

	public static void main(String[] args) throws Throwable {
		new tram_aa_sqr().run();
	}

	BufferedReader br;
	StringTokenizer st;
	PrintWriter out;
	boolean eof = false;
	Random rand = new Random(this.hashCode());

	private void run() throws Throwable {
		Locale.setDefault(Locale.US);
		br = new BufferedReader(new InputStreamReader(System.in));
		out = new PrintWriter(System.out);
		solve();
		out.close();
	}

	String nextToken() {
		while (st == null || !st.hasMoreTokens()) {
			try {
				st = new StringTokenizer(br.readLine());
			} catch (Exception e) {
				eof = true;
				return "0";
			}
		}
		return st.nextToken();
	}

	int nextInt() {
		return Integer.parseInt(nextToken());
	}

	void myAssert(boolean u, String message) {
		if (!u) {
			throw new Error("Assertion failed!!! " + message);
		}
	}

	int inBounds(int x, int l, int r, String name) {
		myAssert(l <= x && x <= r, name + " not in bounds: " + x + " not in ["
				+ l + ".." + r + "]");
		return x;
	}

	String FNAME = "tram";

	int[] x, y;
	int[][] g;
	boolean[] good;

	private void solve() throws IOException {
		int n = inBounds(nextInt(), 2, 100000, "n");
		{
			g = new int[n][];
			int[] x = new int[n - 1];
			int[] y = new int[n - 1];
			int[] c = new int[n];
			for (int i = 0; i < y.length; i++) {
				x[i] = inBounds(nextInt(), 1, n, "b_" + (i + 1)) - 1;
				y[i] = inBounds(nextInt(), 1, n, "e_" + (i + 1)) - 1;
				c[x[i]]++;
				c[y[i]]++;
			}
			for (int i = 0; i < c.length; i++) {
				g[i] = new int[c[i]];
				c[i] = 0;
			}
			for (int i = 0; i < y.length; i++) {
				g[x[i]][c[x[i]]++] = y[i];
				g[y[i]][c[y[i]]++] = x[i];
			}
		}
		int m = inBounds(nextInt(), 0, 100000, "m");
		x = new int[m];
		y = new int[m];
		for (int i = 0; i < m; i++) {
			x[i] = inBounds(nextInt(), 1, n, "x_" + (i + 1)) - 1;
			y[i] = inBounds(nextInt(), 1, n, "y_" + (i + 1)) - 1;
		}
		good = new boolean[n];
		for (int i = 0; i < x.length; i++) {
			dfs(0, 0, x[i], y[i]);
		}
		int ans = -1;
		for (boolean b : good) {
			if (!b) {
				ans++;
			}
		}
		out.println(ans);
	}

	private int dfs(int x, int y, int b, int e) {
		int ans = (x == b ? 1 : 0) + (x == e ? 1 : 0);
		for (int i : g[x]) {
			if (i != y) {
				ans += dfs(i, x, b, e);
			}
		}
		if (ans == 1) {
			good[x] = true;
		}
		return ans;
	}

}
