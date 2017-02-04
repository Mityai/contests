package video;

import java.io.IOException;

/**
 * @author: pashka
 */
public class Main {
    public static void main(String[] args) throws IOException {
        final VideoSourceFactory[] videos = new VideoSourceFactory[12];
//        videos[0] = new ButterfliesVideoSourceFactory(10, 20, false, 0);
//        videos[0] = new GifVideoSourceFactory("pics/pic1.gif");
        for (int i = 0; i < 12; i++) {
            System.out.println("loading pic " + (i + 1));
            videos[i] = new GifVideoSourceFactory("pics/pic" + (i + 1) + ".gif");
        }
//        for (int i = 0; i < 12; i++) {
//            videos[i] = new GifVideoSourceFactory("pic" + (i + 1) + ".gif");
//        }

        new Thread() {
            @Override
            public void run() {
                try {
                    new Server(8001, videos).run();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }.start();
    }
}
