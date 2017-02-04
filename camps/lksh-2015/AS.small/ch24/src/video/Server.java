package video;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.*;

/**
 * @author: pashka
 */
public class Server {

    public static void main(String[] args) throws IOException {
//        new Server(new VideoSourceFactory[]{new ButterfliesVideoSourceFactory(10, 20)}).run();
    }

    private final int PORT;

    VideoSourceFactory[] videos;

    public Server(int port, VideoSourceFactory[] videos) {
        PORT = port;
        this.videos = videos;
    }

    public void run() throws IOException {
        ServerSocket serverSocket = new ServerSocket(PORT);
        System.out.println("server ready");
        while (true) {
            final Socket socket = serverSocket.accept();
            System.out.println("connect: " + socket.getInetAddress());
            new Thread(new PicsSender(socket)).start();
        }
    }


    private class PicsSender implements Runnable {

        private static final long TIMEOUT = 100;
        private final Socket socket;
        private PrintWriter out;
        private Scanner in;

        public PicsSender(Socket socket) throws IOException {
            this.socket = socket;
            out = new PrintWriter(socket.getOutputStream());
            in = new Scanner(socket.getInputStream());
        }

        public void run() {
            VideoSource video = null;
            int userId = -1;
            try {
//                userId = in.nextInt();
                int id = in.nextInt();
                video = videos[id].createVideoSource();
                IndexedImage image = video.getNextFrame();
                out.println(image.width + " " + image.height + " " + image.colors.length);
                for (int i = 0; i < image.colors.length; i++) {
                    String s = Integer.toHexString(image.colors[i]);
                    while (s.length() < 6) s = "0" + s;
                    out.println(s);
                }
                for (int tt = 0; tt < 100; tt++) {
//                    System.out.print(".");
                    image = video.getNextFrame();
                    for (int y = 0; y < image.height; y++) {
                        for (int x = 0; x < image.width; x++) {
                            int i = image.getPixel(x, y);
//                            int i = 0;
                            out.print(encode64(i));
                        }
                    }
                    out.println();
                    out.flush();
                    try {
                        Thread.sleep(TIMEOUT);
                    } catch (InterruptedException e) {
                        return;
                    }
                }
                int ans = in.nextInt();
                video.setAnswer(userId, ans);
            } catch (Exception e) {
                if (userId >= 0 && video != null) {
                    video.setAnswer(userId, 0);
                }
                e.printStackTrace();
            }
        }

//        private String encode(int i) {
//            int r = i & 0xff;
//            int g = (i >> 8) & 0xff;
//            int b = (i >> 16) & 0xff;
////            r = encodeLevel(r);
////            g = encodeLevel(g);
////            b = encodeLevel(b);
////            return "" + encode64(r + (g << 2) + (b << 4));
////            r = (r * 63 + 128) / 255;
////            g = (g * 63 + 128) / 255;
////            b = (b * 63 + 128) / 255;
//            r = (r * 9 + 128) / 255;
//            g = (g * 9 + 128) / 255;
//            b = (b * 9 + 128) / 255;
//            return "" + encode64(r) + encode64(g) + encode64(b);
//        }

        private char encode64(int z) {
//            return (char) (z + '0');
            if (z < 26) return (char)('A' + z);
            if (z < 52) return (char)('a' + z - 26);
            if (z < 62) return (char)('0' + z - 52);
            if (z == 62) return '+';
            return '/';
        }
    }
}
