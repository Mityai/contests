import java.io.*;
import java.util.*;

public class crosses_md_assert implements Runnable {
	private CheckScanner in;
	private PrintWriter out;

	public void run() {
		try {
			solve();
		} catch (IOException e) {
			e.printStackTrace();
			System.exit(1);
		}
	}

	private void solve() throws IOException {
		Locale.setDefault(Locale.US);
		in = new CheckScanner(new File("crosses.in"));
		out = new PrintWriter("crosses.out");
		int n = in.nextInt(3, 2000) + 4;
		int[] a = new int[n + 1];
		for (int i = 5; i <= n; i++) {
			HashSet<Integer> reach = new HashSet<Integer>();
			for (int j = 3; j <= i - 2; j++) {
				reach.add(a[j - 1] ^ a[i - j]);
			}
			while (reach.contains(a[i]))
				a[i]++;
		}
		out.println(a[n] == 0 ? 2 : 1);
		in.close();
		out.close();
	}

	public static void main(String[] args) {
		new Thread(new crosses_md_assert()).start();
	}
}
