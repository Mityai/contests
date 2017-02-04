package video;

import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.IOException;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.Scanner;

/**
 * @author: pashka
 */
public class Client {

    private final int picId;

    public Client(int picId) {
        this.picId = picId;
    }

    public static void main(String[] args) throws IOException, InterruptedException {
        new Client(0).run();
    }

    public void run() throws IOException, InterruptedException {
        Socket socket = null;
        while (socket == null) {
            try {
                socket = new Socket("localhost", 8001);
            } catch (Exception e) {
                Thread.sleep(1000);
            }
        }
        Scanner scanner = new Scanner(socket.getInputStream());
        PrintWriter out = new PrintWriter(socket.getOutputStream());
        out.println(0);
        out.println(picId);
        out.flush();
        int width = scanner.nextInt();
        int height = scanner.nextInt();
        final BufferedImage image = new BufferedImage(width, height, BufferedImage.TYPE_INT_ARGB);
        JFrame frame = new JFrame() {
            @Override
            public void paint(Graphics g) {
                super.paint(g);
                g.drawImage(image, 0, 0, null);
            }
        };
        int c = scanner.nextInt();
        System.out.println(c);
        int[] colors = new int[c];
        for (int i = 0; i < c; i++) {
            colors[i] = Integer.parseInt(scanner.next(), 16);
        }
        frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        frame.setSize(width, height);
        frame.setVisible(true);
        while (true) {
            String s = scanner.next();
            int k = 0;
            for (int y = 0; y < height; y++) {
                for (int x = 0; x < width; x++) {
                    int i = decode(s.charAt(k++));
                    image.setRGB(x, y, colors[i] | 0xff000000);
                }
            }
            frame.repaint();
        }
    }

    private int decode(char c) {
        int z = 0;
        if (c >= 'A' && c <= 'Z') {
            z = c - 'A';
        }
        if (c >= 'a' && c <= 'z') {
            z = c - 'a' + 26;
        }
        if (c >= '0' && c <= '9') {
            z = c - '0' + 52;
        }
        if (c == '+') {
            z = 62;
        }
        if (c == '/') {
            z = 63;
        }
        return z;
    }
}
