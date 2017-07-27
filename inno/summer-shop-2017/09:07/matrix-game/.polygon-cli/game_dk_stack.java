import java.util.*;
import java.io.*;

public class game_dk {
	BufferedReader br;
	PrintWriter out;
	StringTokenizer stok;

	String nextToken() throws IOException {
		while (stok == null || !stok.hasMoreTokens()) {
			String s = br.readLine();
			if (s == null) {
				return null;
			}
			stok = new StringTokenizer(s);
		}
		return stok.nextToken();
	}

	int nextInt() throws IOException {
		return Integer.parseInt(nextToken());
	}

	long nextLong() throws IOException {
		return Long.parseLong(nextToken());
	}

	double nextDouble() throws IOException {
		return Double.parseDouble(nextToken());
	}

	char nextChar() throws IOException {
		return (char) (br.read());
	}

	String nextLine() throws IOException {
		return br.readLine();
	}

	int n, m;
	
	boolean in_field(int x, int y) {
		return ((x >= 0) && (y >= 0) && (x < n) && (y < m));
	}
	
	
	int[][] p = new int[1031][1031];
	int[][] a = new int[1031][1031];
	
	
	int dfs(int i, int j) {
		if (p[i][j] == 0) return 0;
		if (p[i][j] == 1) return 1;
		if (p[i][j] == 2) return -1;
		int x1 = -2;
		int x2 = -2;
		p[i][j] = 2;
		if (in_field(i + a[i][j], j) == true) {
			x1 = dfs(i + a[i][j], j);
		}
		if (in_field(i, j + a[i][j]) == true) {
			x2 = dfs(i, j + a[i][j]);
		}
		if (x1 < 0 && x2 < 0) return -1;
		if (x1 == 0 || x2 == 0) {
			p[i][j] = 1;
			return 1;
		}
		p[i][j] = 0;
		return 0;
	}
	
	void solve() throws IOException {
		n = nextInt();
		m = nextInt();
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				a[i][j] = nextInt();
			}
		}
		int si = nextInt();
		int sj = nextInt();
		si--;
		sj--;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				p[i][j] = -1;
			}
		}

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				p[i][j] = -1;
			}
		}
		
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if ((in_field(i + a[i][j], j)
						|| in_field(i, j + a[i][j])) == false) {
					p[i][j] = 0;
				};
			}
		}
		
		int res = dfs(si, sj);
		if (res == 1) out.println("Anton");
		if (res == 0) out.println("Yasha");
		if (res == -1) out.println("draw");
	}

	void run() throws IOException {
		br = new BufferedReader(new FileReader("game.in"));
		out = new PrintWriter("game.out");
		// br = new BufferedReader(new FileReader("input.txt"));
		// out = new PrintWriter("output.txt");
		// br = new BufferedReader(new InputStreamReader(System.in));
		// out = new PrintWriter(System.out);
		solve();
		br.close();
		out.close();
	}

	public static void main(String[] args) throws IOException {
		// Localea.setDefault(Locale.US);
		new game_dk().run();
	}
}