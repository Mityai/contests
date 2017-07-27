//	������ "�������"
//	������� �������������� ��������-��������� ������ 2009-2010.
//	����� ������ - �������� ��������, ulyantsev@rain.ifmo.ru
//	����� ������� - ���� �����������, nigmatullin@rain.ifmo.ru
//	���������� �������

import java.io.*;
import java.util.*;

public class tram_nn implements Runnable {
	public static void main(String[] args) {
		new tram_nn().run();
	}

	class FastScanner {
		BufferedReader br;
		StringTokenizer st;
		boolean eof;
		String buf;

		public FastScanner(String fileName) throws FileNotFoundException {
			br = new BufferedReader(new FileReader(fileName));
			nextToken();
		}

		public FastScanner(InputStream stream) {
			br = new BufferedReader(new InputStreamReader(stream));
			nextToken();
		}

		String nextToken() {
			while (st == null || !st.hasMoreTokens()) {
				try {
					st = new StringTokenizer(br.readLine());
				} catch (Exception e) {
					eof = true;
					break;
				}
			}
			String ret = buf;
			buf = eof ? "-1" : st.nextToken();
			return ret;
		}

		int nextInt() {
			return Integer.parseInt(nextToken());
		}

		long nextLong() {
			return Long.parseLong(nextToken());
		}

		double nextDouble() {
			return Double.parseDouble(nextToken());
		}

		void close() {
			try {
				br.close();
			} catch (Exception e) {

			}
		}

		boolean isEOF() {
			return eof;
		}
	}

	FastScanner sc;
	PrintWriter out;

	private static final String FN = "tram";

	public void run() {
		Locale.setDefault(Locale.US);
		try {
			sc = new FastScanner(System.in);
			out = new PrintWriter(System.out);
			solve();
			sc.close();
			out.close();
		} catch (Throwable e) {
			e.printStackTrace();
			System.exit(1);
		}
	}

	void doAssert(boolean isRight, String s) {
		if (!isRight)
			throw new AssertionError(s);
	}

	ArrayList<Integer>[] edges;
	int[][] dp;
	int[] parent, level, lca, begin;
	int n, ans;

	int dfs2(int x) {
		int ret = begin[x];
		for (int i : edges[x]) {
			if (i == parent[x]) {
				continue;
			}
			int got = dfs2(i);
			if (got == 0) {
				++ans;
			}
			ret += got;
		}
		return ret - 2 * lca[x];
	}

	void preCalcLCA() {
		for (int i = 0; i < n; i++) {
			dp[0][i] = parent[i];
		}
		for (int i = 1; i < dp.length; i++) {
			for (int j = 0; j < n; j++) {
				if (dp[i - 1][j] == -1) {
					dp[i][j] = -1;
				} else {
					dp[i][j] = dp[i - 1][dp[i - 1][j]];
				}
			}
		}
	}

	int getLCA(int x, int y) {
		if (level[x] > level[y]) {
			int tmp = x;
			x = y;
			y = tmp;
		}
		int difL = level[y] - level[x];
		int m = Integer.numberOfTrailingZeros(Integer.highestOneBit(n)) + 2;
		for (int i = m; i >= 0; i--) {
			if (difL >= (1 << i)) {
				difL -= 1 << i;
				y = dp[i][y];
			}
		}
		if (x == y) {
			return x;
		}
		for (int i = m; i >= 0; i--) {
			if (dp[i][x] != dp[i][y]) {
				x = dp[i][x];
				y = dp[i][y];
			}
		}
		return parent[x];
	}

	void dfs1(int x, int parent, int level) {
		doAssert(this.parent[x] == -2, "it's not a tree");
		this.parent[x] = parent;
		this.level[x] = level;
		for (int i : edges[x]) {
			if (i == parent) {
				continue;
			}
			dfs1(i, x, level + 1);
		}
	}

	private void solve() {
		n = sc.nextInt();
		doAssert(2 <= n && n <= 100000, "n is out of bounds");
		edges = new ArrayList[n];
		parent = new int[n];
		lca = new int[n];
		level = new int[n];
		begin = new int[n];
		dp = new int[Integer.toBinaryString(n).length() + 2][n];
		Arrays.fill(parent, -2);
		for (int i = 0; i < n; i++) {
			edges[i] = new ArrayList<Integer>();
		}
		for (int i = 0; i < n - 1; i++) {
			int x = sc.nextInt() - 1;
			int y = sc.nextInt() - 1;
			doAssert(0 <= x && x < n && 0 <= y && y < n && x != y, "invalid edge: line "
					+ (i + 2));
			edges[x].add(y);
			edges[y].add(x);
		}
		dfs1(0, -1, 0);
		for (int i = 0; i < n; i++) {
			doAssert(parent[i] != -2, "it's not a tree");
		}
		preCalcLCA();
		int m = sc.nextInt();
		doAssert(0 <= m && m <= 100000, "m is out of bounds");
		for (int i = 0; i < m; i++) {
			int x = sc.nextInt() - 1;
			int y = sc.nextInt() - 1;
			doAssert(0 <= x && x < n && 0 <= y && y < n && x != y,
					"invalid number of vertices: line " + (i + n + 3));
			begin[x]++;
			begin[y]++;
			lca[getLCA(x, y)]++;
		}
		ans = 0;
		dfs2(0);
		out.println(ans);
	}
}
