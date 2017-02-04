package game;

import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.awt.image.DataBufferInt;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.*;

/**
 * @author: pashka
 */
public class GameServer {

    private static final int PLAYERS_NUM = 12;
    private static final int TANK_R = 5;
    private static final int BOMB_R = 2;
    private static final double FIRE_TIMEOUT = 5;
    private static final double DT = 0.1;
    private static final double G = 9.8;
    private static final double ROUND_TIME = 60;
    private static final int PORT = 8000;
    private static double DAMAGE_R = 50;
    private static final int MAX_DAMAGE = 80;
    private static int SCREEN_WIDTH = 1000;
    private static int SCREEN_HEIGHT = 700;

    private static double FIELD_WIDTH = 1000;
    private static double EXPLODE_R = 20;
    private BufferedImage image;

    private static final Color[] colors = new Color[PLAYERS_NUM];

    static {
        for (int i = 0; i < PLAYERS_NUM; i++) {
            colors[i] = Color.getHSBColor((float) (i * 1.0 / PLAYERS_NUM), 1, 1f);
            colors[4] = Color.WHITE;
        }
    }

    int[] score = new int[PLAYERS_NUM];

    Tank[] tanks;
    Set<Bomb> bombs;
    String[] nicks;

    int[] field = new int[SCREEN_WIDTH];
    private double currentTime;

    public static void main(String[] args) throws InterruptedException, FileNotFoundException {
        Locale.setDefault(Locale.US);
        new GameServer().run();
    }

    private void run() throws InterruptedException, FileNotFoundException {
        image = new BufferedImage(SCREEN_WIDTH, SCREEN_HEIGHT, BufferedImage.TYPE_INT_RGB);

        JPanel imagePane = new JPanel() {
            @Override
            public void paint(Graphics g) {
                g.drawImage(image, 0, 0, null);
            }
        };
        imagePane.setSize(SCREEN_WIDTH, SCREEN_HEIGHT);
        imagePane.setMinimumSize(new Dimension(SCREEN_WIDTH, SCREEN_HEIGHT));
        imagePane.setPreferredSize(new Dimension(SCREEN_WIDTH, SCREEN_HEIGHT));

        final JFrame frame = new JFrame("Tank battle");
//        frame.setExtendedState(JFrame.MAXIMIZED_BOTH);
//        frame.setUndecorated(true);
        frame.getContentPane().setLayout(new BorderLayout());

        frame.getContentPane().add(imagePane, BorderLayout.CENTER);

        frame.pack();
        frame.setVisible(true);
        frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);


        tanks = new Tank[PLAYERS_NUM];
        nicks = new String[PLAYERS_NUM];
        for (int i = 0; i < PLAYERS_NUM; i++) {
            nicks[i] = "Player " + i;
        }

        new Thread() {
            @Override
            public void run() {
                try {
                    ServerSocket serverSocket = new ServerSocket(PORT);
                    while (true) {
                        final Socket socket = serverSocket.accept();
                        new Thread() {
                            @Override
                            public void run() {
                                try {
                                    Scanner in = new Scanner(socket.getInputStream());
                                    PrintWriter out = new PrintWriter(socket.getOutputStream());
                                    int id = getPlayerId(in.nextInt());
                                    if (id == -1) return;
                                    String nick = in.next();
                                    if (nick.length() > 10) nick = nick.substring(0, 10) + "...";
                                    nicks[id] = nick;
                                    if (id == -1) return;
                                    while (true) {
                                        printGameState(out, id);
                                        double an = in.nextDouble();
                                        double v = in.nextDouble();
                                        fire(tanks[id], an, v);
                                        Thread.sleep(100);
                                    }
                                } catch (IOException e) {
                                    e.printStackTrace();
                                } catch (InterruptedException e) {
                                    e.printStackTrace();
                                }
                            }

                        }.start();
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        }.start();

        while (true) {
            File file = new File("scores.txt");
            if (file.exists()) {
                Scanner in = new Scanner(file);
                for (int i = 0; i < PLAYERS_NUM; i++) {
                    score[i] = in.nextInt();
                }
                in.close();
            }
            initField();
            currentTime = 0;
            while (currentTime < ROUND_TIME) {
                move();
                draw();
                frame.repaint();
                Thread.sleep(50);
            }
            PrintWriter out = new PrintWriter(file);
            for (int i = 0; i < PLAYERS_NUM; i++) {
                out.println(score[i]);
            }
            out.close();
        }
    }

    private void printGameState(PrintWriter out, int myid) {
        Tank[] tankCopy = null;
        Set<Bomb> bombsCopy = null;
        synchronized (tanks) {
            tankCopy = tanks.clone();
            for (int i = 0; i < PLAYERS_NUM; i++) {
                int j = random.nextInt(i + 1);
                if (i != myid && j != myid) {
                    Tank t = tankCopy[i];
                    tankCopy[i] = tankCopy[j];
                    tankCopy[j] = t;
                }
            }
            bombsCopy = new HashSet<>(bombs);
        }
        out.println(PLAYERS_NUM + " " + bombs.size() + " " + myid);
        for (Tank tank : tankCopy) {
            if (tank.isAlive()) {
                out.println(tank.x + " " + tank.getY() + " " + tank.hp);
            } else {
                out.println("0 0 0");
            }
        }
        for (Bomb bomb : bombsCopy) {
            out.println(bomb.x + " " + bomb.y + " " + bomb.vx + " " + bomb.vy);
        }
        out.flush();
    }

    int[] codes = {23953330, 228, 239239, 567432, 876876, 7, 280, 123};

    private int getPlayerId(int code) {
        for (int i = 0; i < codes.length; i++) {
            if (codes[i] == code) return i;
        }
        return -1;
    }

    private void move() {
        synchronized (tanks) {
            currentTime += DT;
            for (Bomb bomb : new ArrayList<>(bombs)) {
                if (bomb.exploding) {
                    bombs.remove(bomb);
                } else {
                    bomb.x += bomb.vx * DT;
                    bomb.y += bomb.vy * DT;
                    bomb.vy -= G * DT;
                    if (bomb.x < 0 || bomb.x > FIELD_WIDTH) {
                        bombs.remove(bomb);
                    } else {
                        int x = coordToScreen(bomb.x);
                        int y = coordToScreen(bomb.y);
                        if (y < field[x]) {
                            explode(bomb);
                            bomb.exploding = true;
                        }
                    }
                }
            }
            fire(tanks[PLAYERS_NUM - 1], -45 + random.nextDouble() * 90, 50 + random.nextDouble() * 50);
        }
    }

    private void explode(Bomb bomb) {

        for (Tank tank : tanks)
            if (tank.isAlive()) {
                double dx = tank.x - bomb.x;
                double dy = tank.getY() - bomb.y;
                double d = Math.sqrt(dx * dx + dy * dy);
                if (d <= DAMAGE_R) {
                    tank.hp -= getDamage(d);
                    if (tank.hp < 0) tank.hp = 0;
                    if (tank.hp <= 0) {
                        if (tank == bomb.owner) {
//                        score[bomb.owner.id]--;
                        } else {
                            score[bomb.owner.id]++;
                        }
                    }
                }
            }

        int r = coordToScreen(EXPLODE_R);
        int x = coordToScreen(bomb.x);
        int y = coordToScreen(bomb.y);
        for (int dx = -r; dx <= r; dx++) {
            int dy = (int) Math.sqrt(r * r - dx * dx);
            if (x + dx >= 0 && x + dx < SCREEN_WIDTH) {
                if (y - dy < field[x + dx]) {
                    field[x + dx] -= Math.min(field[x + dx], y + dy) - (y - dy);
                }
            }
        }
    }

    private int getDamage(double d) {
        return (int) (MAX_DAMAGE * (DAMAGE_R - d) / DAMAGE_R);
    }

    private void draw() {
        int[] data = ((DataBufferInt) image.getRaster().getDataBuffer()).getData();
        for (int y = 0; y < SCREEN_HEIGHT; y++) {
            for (int x = 0; x < SCREEN_WIDTH; x++) {
                int c = field[x] > SCREEN_HEIGHT - y - 1 ? color(0, 100 - 50 * (y + random.nextInt(50)) / SCREEN_HEIGHT, 0) :
                        color(0, 0, 50 + 100 * (y + random.nextInt(50)) / SCREEN_HEIGHT);
                data[y * SCREEN_WIDTH + x] = c | 0xff000000;
            }
        }
        Graphics2D g = (Graphics2D) image.getGraphics();
        for (Tank tank : tanks)
            if (tank.isAlive()) {
                int x = coordToScreen(tank.x);
                int y = SCREEN_HEIGHT - coordToScreen(tank.getY());
                g.setColor(tank.color);
                g.fillOval(x - TANK_R, y - TANK_R, 2 * TANK_R, 2 * TANK_R);
                g.drawString("" + tank.hp, x - 5, y + 20);
            }
        for (Bomb bomb : bombs) {
            int x = coordToScreen(bomb.x);
            int y = SCREEN_HEIGHT - coordToScreen(bomb.y);
            if (bomb.exploding) {
                g.setColor(Color.RED);
                int r = coordToScreen(EXPLODE_R);
                g.fillOval(x - r, y - r, 2 * r, 2 * r);
                g.setColor(Color.YELLOW);
                r /= 2;
                g.fillOval(x - r, y - r, 2 * r, 2 * r);
            } else {
                int dx = coordToScreen(bomb.vx * 0.1);
                int dy = -coordToScreen(bomb.vy * 0.1);
                g.setColor(Color.white);
//                g.drawLine(x, y, x - dx, y - dy);
                g.fillOval(x - dx - BOMB_R / 2, y - dy - BOMB_R / 2, BOMB_R, BOMB_R);
                g.fillOval(x - 2 * dx - BOMB_R / 2, y - 2 * dy - BOMB_R / 2, BOMB_R, BOMB_R);
                g.setColor(bomb.owner.color);
                g.fillOval(x - BOMB_R, y - BOMB_R, 2 * BOMB_R, 2 * BOMB_R);
            }
        }
        for (int i = 0; i < PLAYERS_NUM; i++) {
            if (tanks[i].isAlive())
                g.setColor(colors[i]);
            else
                g.setColor(Color.gray);
//            int x = (int) (SCREEN_WIDTH * (0.5 + i) / PLAYERS_NUM);
            g.drawString(nicks[i] + ": " + score[i], 5, 20 + 15 * i);
        }
    }

    private int coordToScreen(double x) {
        return (int) (x * SCREEN_WIDTH / FIELD_WIDTH);
    }

    private double screenToCoord(int x) {
        return 1.0 * (x * FIELD_WIDTH) / SCREEN_WIDTH;
    }

    private int color(int r, int g, int b) {
        return (r << 16) + (g << 8) + b;
    }

    Random random = new Random();

    private void initField() {
        int N = 10;
        int[] x = new int[N];
        double[] dy = new double[N];
        while (true) {
            for (int i = 0; i < N; i++) {
                x[i] = random.nextInt(SCREEN_WIDTH);
                dy[i] = random.nextDouble() * 2 - 1;
            }
            x[0] = 0;
            x[1] = SCREEN_WIDTH;
            Arrays.sort(x);
            boolean ok = true;
            double y = random.nextDouble() * SCREEN_HEIGHT / 2 + SCREEN_HEIGHT / 4;
            for (int i = 0; i < N - 1; i++) {
                for (int xx = x[i]; xx < x[i + 1]; xx++) {
                    double dyy = dy[i] + (dy[i + 1] - dy[i]) * (xx - x[i]) / (x[i + 1] - x[i]);
                    y += dyy;
                    field[xx] = (int) y;
                    if (field[xx] < SCREEN_HEIGHT / 4 || field[xx] > SCREEN_HEIGHT * 3 / 4) ok = false;
                }
            }
            if (ok) break;
        }

        for (int i = 0; i < PLAYERS_NUM; i++) {
            tanks[i] = new Tank();
            tanks[i].color = colors[i];
            tanks[i].hp = 100;
            tanks[i].x = random.nextDouble() * FIELD_WIDTH;
            tanks[i].id = i;
        }

        bombs = new HashSet<>();
    }

    void fire(Tank tank, double angle, double v) {
        if (currentTime < tank.timeLastFired + FIRE_TIMEOUT || !tank.isAlive() || v < 0 || v > 100) {
            return;
        }
        Bomb bomb = new Bomb();
        bomb.x = tank.x;
        bomb.y = tank.getY();
        bomb.vx = v * Math.sin(angle * Math.PI / 180);
        bomb.vy = v * Math.cos(angle * Math.PI / 180);
        bomb.owner = tank;
        tank.timeLastFired = currentTime;
        bombs.add(bomb);
    }

    class Tank {
        double x;
        int id;

        double getY() {
            int xx = coordToScreen(x);
            if (xx < 0) xx = 0;
            if (xx >= SCREEN_WIDTH) xx = SCREEN_WIDTH - 1;
            return screenToCoord(field[xx]);
        }

        Color color;
        int hp;
        double timeLastFired = Integer.MIN_VALUE;

        boolean isAlive() {
            return hp > 0;
        }
    }

    class Bomb {
        double x;
        double y;
        double vx;
        double vy;
        boolean exploding;
        Tank owner;
    }
}
