import java.io.*;
import java.util.*;
import java.math.*;

public class mail_nn_DFS implements Runnable {

	ArrayList<Integer>[] edges;

	void solve() {
		int n = sc.nextInt();
		int[] h = new int[n];
		boolean[] was = new boolean[n];
		edges = new ArrayList[n];
		for (int i = 0; i < n; i++) {
			h[i] = sc.nextInt();
			edges[i] = new ArrayList<Integer>();
		}
		for (int i = 0; i + 1 < n; i++) {
			int from = sc.nextInt() - 1;
			int to = sc.nextInt() - 1;
			edges[from].add(to);
			edges[to].add(from);
		}
		int q = sc.nextInt();
		for (int i = 0; i < q; i++) {
			char ch = sc.nextToken().charAt(0);
			if (ch == '!') {
				int x = sc.nextInt() - 1;
				int height = sc.nextInt();
				h[x] = height;
			} else {
				int x = sc.nextInt() - 1;
				int y = sc.nextInt() - 1;
				Arrays.fill(was, false);
				out.println(dfs(x, y, h, was, 0));
			}
		}
	}

	int dfs(int x, int target, int[] h, boolean[] was, int max) {
		if (x == target) {
			return Math.max(max, h[x]);
		}
		was[x] = true;
		for (int i : edges[x]) {
			if (was[i]) {
				continue;
			}
			int got = dfs(i, target, h, was, Math.max(max, h[x]));
			if (got != Integer.MIN_VALUE) {
				return got;
			}
		}
		return Integer.MIN_VALUE;
	}

	FastScanner sc;
	PrintWriter out;

	public void run() {
		Locale.setDefault(Locale.US);
		try {
			sc = new FastScanner("mail.in");
			out = new PrintWriter("mail.out");
			solve();
			sc.close();
			out.close();
		} catch (Throwable e) {
			e.printStackTrace();
			System.exit(1);
		}
	}

	class FastScanner extends BufferedReader {
		StringTokenizer st;
		boolean eof;
		String buf;
		String curLine;
		boolean createST;

		public FastScanner(String fileName) throws FileNotFoundException {
			this(fileName, true);
		}

		public FastScanner(String fileName, boolean createST)
				throws FileNotFoundException {
			super(new FileReader(fileName));
			this.createST = createST;
			nextToken();
		}

		public FastScanner(InputStream stream) {
			this(stream, true);
		}

		public FastScanner(InputStream stream, boolean createST) {
			super(new InputStreamReader(stream));
			this.createST = createST;
			nextToken();
		}

		String nextLine() {
			String ret = curLine;
			if (createST) {
				st = null;
			}
			nextToken();
			return ret;
		}

		String nextToken() {
			if (!createST) {
				try {
					curLine = readLine();
				} catch (Exception e) {
					eof = true;
				}
				return null;
			}
			while (st == null || !st.hasMoreTokens()) {
				try {
					curLine = readLine();
					st = new StringTokenizer(curLine);
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

		BigInteger nextBigInteger() {
			return new BigInteger(nextToken());
		}

		public void close() {
			try {
				buf = null;
				st = null;
				curLine = null;
				super.close();
			} catch (Exception e) {

			}
		}

		boolean isEOF() {
			return eof;
		}
	}

	public static void main(String[] args) {
		new mail_nn_DFS().run();
	}
}
