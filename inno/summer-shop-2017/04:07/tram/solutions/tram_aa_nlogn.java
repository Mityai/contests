// ������ "�������"
// ������� �������������� ��������-��������� ������ 2009-2010.
// ����� ������: �������� ��������, ulyantsev@rain.ifmo.ru
// ����� �������: ����� ���, akhi@rain.ifmo.ru

import java.io.*;
import java.util.*;
import java.math.*;

public class tram_aa_nlogn {

	public static void main(String[] args) throws Throwable {
		new tram_aa_nlogn().run();
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

	int[] x2, y2;
	int[] h, mark;
	int[][] g, a;

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
		x2 = new int[m];
		y2 = new int[m];
		for (int i = 0; i < m; i++) {
			x2[i] = inBounds(nextInt(), 1, n, "x_" + (i + 1)) - 1;
			y2[i] = inBounds(nextInt(), 1, n, "y_" + (i + 1)) - 1;
		}
		int log = Integer.numberOfTrailingZeros(Integer.highestOneBit(n));
		a = new int[n][log];
		h = new int[n];
		mark = new int[n];
		dfs(0, 0, 0);
		for (int i = 0; i < x2.length; i++) {
			int x = x2[i];
			int y = y2[i];
			mark[x]++;
			mark[y]++;
			{
				int k = log - 1;
				while (h[x] > h[y]) {
					while (h[a[x][k]] < h[y]) {
						k--;
					}
					x = a[x][k];
				}
			}
			{
				int k = log - 1;
				while (h[y] > h[x]) {
					while (h[a[y][k]] < h[x]) {
						k--;
					}
					y = a[y][k];
				}
			}
			int k = log - 1;
			while (x != y) {
				while (k > 0 && a[x][k] == a[y][k]) {
					k--;
				}
				x = a[x][k];
				y = a[y][k];
			}
			mark[x] -= 2;
		}
		dfs2(0, 0);
		out.println(ans);
	}

	private int dfs2(int x, int y) {
		int z = mark[x];
		for (int i : g[x]) {
			if (i != y) {
				z += dfs2(i, x);
			}
		}
		if (z == 0) {
			ans++;
		}
		return z;
	}

	int ans = -1;

	private void dfs(int x, int y, int height) {
		h[x] = height;
		a[x][0] = y;
		for (int i = 1; i < a[x].length; i++) {
			a[x][i] = a[a[x][i - 1]][i - 1];
		}
		for (int i : g[x]) {
			if (i != y) {
				dfs(i, x, height + 1);
			}
		}
	}

}
