import java.io.BufferedReader;
import java.io.FileReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.StringTokenizer;

public class tram_sm_slow {
	class Pair {
		int x, y;

		public Pair(int x, int y) {
			this.x = x;
			this.y = y;
		}

	}

	ArrayList<Integer>[] e;

	@SuppressWarnings("unchecked")
	void solve() {
		int n = nextInt();
		assert 1 <= n && n <= 100000;
		e = new ArrayList[n];
		for (int i = 0; i < e.length; i++) {
			e[i] = new ArrayList<Integer>();
		}
		Pair[] p = new Pair[n - 1];
		for (int i = 0; i < n - 1; i++) {
			int x = nextInt() - 1;
			int y = nextInt() - 1;
			p[i] = new Pair(x, y);
		}

		int m = nextInt();
		Pair[] req = new Pair[m];
		for (int i = 0; i < m; i++) {
			int x = nextInt() - 1;
			int y = nextInt() - 1;
			assert x != y;
			req[i] = new Pair(x, y);
		}
		int ans = 0;
		for (int i = 0; i < p.length; i++) {
			for (int j = 0; j < e.length; j++) {
				e[j].clear();
			}
			for (int j = 0; j < p.length; j++) {
				if (i == j)
					continue;
				e[p[j].x].add(p[j].y);
				e[p[j].y].add(p[j].x);
			}
			boolean ok = true;
			for (Pair r : req) {
				if (!dfs(r.x, -1, r.y)) {
					ok = false;
					break;
				}
			}
			if (ok) {
				ans++;
			}
		}
		out.println(ans);
	}

	boolean[] u;

	private boolean dfs(int v, int prev, int y) {
		if (v == y)
			return true;
		for (int i : e[v]) {
			if (i == prev)
				continue;
			if (dfs(i, v, y)) {
				return true;
			}
		}
		return false;
	}

	BufferedReader br;
	StringTokenizer st;
	PrintWriter out;

	public void run() {
		br = new BufferedReader(new InputStreamReader(System.in));
		out = new PrintWriter(System.out);
		solve();
		out.close();
	}

	String nextToken() {
		try {
			while (st == null || !st.hasMoreTokens()) {
				String s = br.readLine();
				if (s == null) {
					return null;
				}
				st = new StringTokenizer(s);
			}
			return st.nextToken();
		} catch (IOException e) {
			throw new RuntimeException();
		}
	}

	int nextInt() {
		return Integer.parseInt(nextToken());
	}

	long nextLong() {
		return Integer.parseInt(nextToken());
	}

	public static void main(String[] args) {
		new tram_sm_slow().run();
	}
}
