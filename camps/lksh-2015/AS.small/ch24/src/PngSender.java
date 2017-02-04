import sun.misc.IOUtils;
import sun.nio.ch.IOUtil;
import video.Server;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Random;
import java.util.Scanner;

/**
 * @author: pashka
 */
public class PngSender {

    private static final int PICS_NUM = 15;
    private static final int LEN = 1024;

    public static void main(String[] args) throws IOException {
//
        final byte[][] pics = new byte[PICS_NUM][];
        for (int i = 0; i < PICS_NUM; i++) {
            pics[i] = loadFile("pics/" + (i + 1) + ".png");
        }
        final ServerSocket serverSocket = new ServerSocket(9000);
        final Random random = new Random();
        while (true) {
            final Socket socket = serverSocket.accept();
            new Thread() {
                @Override
                public void run() {
                    try {
                        System.out.println(socket.getInetAddress());
                        int i = new Scanner(socket.getInputStream()).nextInt();
                        byte[] pic = pics[i % PICS_NUM];
                        for (int o = 0; o < pic.length; o += LEN) {
                            socket.getOutputStream().write(pic, o, Math.min(LEN, pic.length - o));
                            socket.getOutputStream().flush();
                        }
                        socket.close();
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }
            }.start();
        }
    }

    private static byte[] loadFile(String s) throws IOException {
        return Files.readAllBytes(Paths.get(s));
    }
}
