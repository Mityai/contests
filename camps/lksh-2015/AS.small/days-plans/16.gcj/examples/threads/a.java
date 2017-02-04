import java.lang.Thread;

public class a {

	static public class SubThread extends Thread {
		private int x;
		public SubThread( int x ) {
			this.x = x;
		}
		public void run() {
			while (true)
				;//System.out.println(x);
		}
	}

	public static void main( String[] args ) {
		new SubThread(1).start();
		new SubThread(2).start();
		new SubThread(3).start();
		new SubThread(4).start();
        while (true)
			;//System.out.println("main");
	}
}