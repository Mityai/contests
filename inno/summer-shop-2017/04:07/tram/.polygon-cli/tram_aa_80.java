// ������ "�������"
// ������� �������������� ��������-��������� ������ 2009-2010.
// ����� ������: �������� ��������, ulyantsev@rain.ifmo.ru
// ����� �������: ����� ���, akhi@rain.ifmo.ru
// ����������� �� 80 ������ - ������ ���������

import java.io.*;
import java.util.*;
import java.math.*;

public class tram_aa_80 {

	public static void main(String[] args) throws Throwable {
		new tram_aa_80().run();
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
		myAssert(l <= x && x <= r, name + " not in bounds: " + x + " not in [" + l + ".." + r + "]");
		return x;
	}

	String FNAME = "tram";

	int[] x, y, u, c, mark;
	int[][] g, r;

	private void solve() throws IOException {
		int n = inBounds(nextInt(), 2, 100000, "n");
		if (n > 1000) {
			out.println("This test is hard :)");
			return;
		}
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
		x = new int[2 * m];
		y = new int[2 * m];
		for (int i = 0; i < m; i++) {
			x[2 * i] = inBounds(nextInt(), 1, n, "x_" + (i + 1)) - 1;
			y[2 * i] = inBounds(nextInt(), 1, n, "y_" + (i + 1)) - 1;
			x[2 * i + 1] = y[2 * i];
			y[2 * i + 1] = x[2 * i];
		}
		{
			r = new int[n][];
			int[] c = new int[n];
			for (int i = 0; i < y.length; i++) {
				c[x[i]]++;
			}
			for (int i = 0; i < c.length; i++) {
				r[i] = new int[c[i]];
				c[i] = 0;
			}
			for (int i = 0; i < y.length; i++) {
				r[x[i]][c[x[i]]++] = i;
			}
		}
		u = new int[n];
		for (int i = 0; i < u.length; i++) {
			u[i] = i;
		}
		c = new int[n];
		mark = new int[n];
		dfs(0);
		dfs2(0);
		out.println(ans);
	}

	private int dfs2(int x) {
		c[x] = 0;
		int y = mark[x];
		for (int i : g[x]) {
			if (c[i] == 2) {
				y += dfs2(i);
			}
		}
		if (y == 0) {
			ans++;
		}
		return y;
	}

	int ans = -1;

	private void dfs(int x) {
		c[x] = 1;
		for (int i : g[x]) {
			if (c[i] > 0) {
				continue;
			}
			dfs(i);
			union(x, i);
		}
		for (int i : r[x]) {
			if (c[y[i]] == 2) {
				int z = get(y[i]);
				mark[z] -= 2;
				mark[y[i]]++;
				mark[x]++;
			}
		}
		c[x] = 2;
	}

	private void union(int x, int i) {
		u[get(i)] = get(x);
	}

	private int get(int x) {
		if (u[x] != x) {
			u[x] = get(u[x]);
		}
		return u[x];
	}

}
