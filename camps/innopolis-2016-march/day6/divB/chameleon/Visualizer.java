import javax.swing.*;
import javax.swing.Timer;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.*;
import java.util.*;
import java.awt.image.BufferedImage;
import javax.imageio.ImageIO;

public class Visualizer extends JPanel {
    public static final Insets INSETS = new Insets(3, 3, 3, 3);
    String solution;
    int n;
    char[][] need;
    char[][] current;
    int curX, curY;
    int solutionPtr;
    JCheckBox mistakesHighlightButton;

    boolean paused = true;
    Deque<Character> oldLog = new ArrayDeque<>();
    boolean mistakesHighlight = false;
    boolean runningWithoutOutput = false;

    static final int SIZE = 400;
    static final int MAX_DELAY = 301;
    private Grid currentGrid;
    private AbstractAction pausedAction;
    private AbstractAction stepBackAction = new AbstractAction("Шаг назад") {
        @Override
        public void actionPerformed(ActionEvent e) {
            oneStepBackward();
        }
    };
    private AbstractAction stepForwardAction = new AbstractAction("Шаг вперед") {
        @Override
        public void actionPerformed(ActionEvent e) {
            oneStepForward();
        }
    };
    private AbstractAction toEndAction = new AbstractAction("В конец") {
        @Override
        public void actionPerformed(ActionEvent e) {
            while (oneStepForward()) {}
        }
    };
    private AbstractAction toBeginAction = new AbstractAction("В начало") {
        @Override
        public void actionPerformed(ActionEvent e) {
            reset();
        }
    };
    private JLabel solutionLabel;
    private boolean error;

    public static void showSelection() {
        final JFrame frame = new JFrame("РОИ-2013. Хамелеон");
        final JFileChooser chooser = new JFileChooser();
        frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);

        JPanel panel = new JPanel(new BorderLayout());
        JPanel buttonsPane = new JPanel(new FlowLayout());
        JPanel inputPane = new JPanel(new GridBagLayout());
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.insets = INSETS;
        inputPane.add(new JLabel("Входной файл"), gbc);
        final JTextField inputFileField = new JTextField(new File(new File(".").getAbsoluteFile(), "chameleon.in").toString(), 30);
        inputPane.add(inputFileField, gbc);
        gbc.gridwidth = GridBagConstraints.REMAINDER;
        inputPane.add(new JButton(new AbstractAction("Выбрать...") {
            @Override
            public void actionPerformed(ActionEvent e) {
                chooser.setSelectedFile(new File(inputFileField.getText()));
                chooser.setDialogTitle("Выберите входной файл");
                if (chooser.showOpenDialog(frame) == JFileChooser.APPROVE_OPTION) {
                    inputFileField.setText(chooser.getSelectedFile().toString());
                }
            }
        }), gbc);
        gbc.gridwidth = 1;
        gbc.gridy = 2;
        inputPane.add(new JLabel("Выходной файл"), gbc);
        final JTextField outputFileField = new JTextField(new File(new File(".").getAbsoluteFile(), "chameleon.out").toString(), 30);
        inputPane.add(outputFileField, gbc);
        inputPane.add(new JButton(new AbstractAction("Выбрать...") {
            @Override
            public void actionPerformed(ActionEvent e) {
                chooser.setSelectedFile(new File(outputFileField.getText()));
                chooser.setDialogTitle("Выберите выходной файл");
                if (chooser.showOpenDialog(frame) == JFileChooser.APPROVE_OPTION) {
                    outputFileField.setText(chooser.getSelectedFile().toString());
                }
            }
        }), gbc);

        panel.add(inputPane, BorderLayout.CENTER);
        buttonsPane.add(new JButton(new AbstractAction("Показать") {
            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    main(inputFileField.getText(), outputFileField.getText());
                } catch (Exception e1) {
                    e1.printStackTrace();
                }
            }
        }));
        buttonsPane.add(new JButton(new AbstractAction("Выйти") {
            @Override
            public void actionPerformed(ActionEvent e) {
                System.exit(0);
            }
        }));
        panel.add(buttonsPane, BorderLayout.PAGE_END);
        frame.add(panel);
        frame.pack();
        frame.setVisible(true);
        frame.setLocationRelativeTo(null);
        frame.setResizable(false);
    }

    final Timer timer = new Timer(10, new ActionListener() {
        @Override
        public void actionPerformed(ActionEvent e) {
            SwingUtilities.invokeLater(new Runnable() {
                @Override
                public void run() {
                    if (!paused) {
                        if (!oneStepForward()) {
                            setPaused(true);
                        }
                    }
                }
            });
        }
    });

    public static void main(String... args) throws Exception {
        Locale.setDefault(Locale.US);
        if (args.length == 0) {
            showSelection();
            return;
        }

        final JFrame frame = new JFrame("РОИ-2013. Хамелеон");
        frame.setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
        frame.setResizable(false);
        final Visualizer me;
        try {
            if (args.length == 1) {
                me = new Visualizer(args[0], "");
            } else {
                me = new Visualizer(args[0], args[1]);
            }
        } catch (Exception e) {
            e.printStackTrace();
            return;
        }
        frame.add(me);
        frame.pack();
        frame.setVisible(true);
        frame.setLocationRelativeTo(null);
        frame.addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosed(WindowEvent e) {
                me.timer.stop();
            }
        });
    }

    public Visualizer(String input, String output/*, String image*/) throws Exception {
        try {
            Scanner in = new Scanner(new File(input));
            try {
                n = in.nextInt();
            } catch (InputMismatchException e) {
                throw new AssertionError("В первой строке ожидалось число", e);
            }
            assert 1 <= n && n <= 100 : "N не принадлежит отрезков [1, 100]";
            need = new char[n][n];
            for (int i = 0; i < n; i++) {
                String tmp = in.next();
                assert tmp.length() == n : "Строка " + (i + 1) + " имеет длину не равную N";
                for (int j = 0; j < n; j++) {
                    need[i][j] = tmp.charAt(j);
                    assert need[i][j] == 'W' || need[i][j] == 'B' : "В позиции (" + (i + 1) + ", " + (j + 1) + ") неизвестный символ";
                }
            }
            in.close();
        } catch (NoSuchElementException e) {
            reportError("Ошибка чтения входного файла", "Неожиданный конец файла");
            throw e;
        } catch (FileNotFoundException e) {
            reportError("Ошибка чтения входного файла", "Входной файл не найден");
            throw e;
        } catch (AssertionError e) {
            reportError("Ошибка чтения входного файла", e.getMessage());
            throw e;
        } catch (Exception e) {
            reportError("Ошибка чтения входного файла", "Неизвестная ошибка\n" + e.getMessage());
            throw e;
        }

        try {
            BufferedReader out = new BufferedReader(new FileReader(new File(output)));
            solution = out.readLine();
            out.close();

            for (int i = 0; i < solution.length(); i++) {
                char c = solution.charAt(i);
                assert names.indexOf(Character.toLowerCase(c)) != -1 : "Неизвестный символ на позиции " + (i + 1);
            }
        } catch (FileNotFoundException e) {
            JOptionPane.showMessageDialog(
                    this,
                    "Выходной файл не найден\nБудут показываться только входные данные",
                    "Ошибка чтения выходного файла",
                    JOptionPane.INFORMATION_MESSAGE

            );
            solution = "";
            runningWithoutOutput = true;
        } catch (NoSuchElementException e) {
            reportError("Ошибка чтения выходного файла", "Неверный формат выходного файла");
            throw e;
        } catch (IOException | AssertionError e) {
            reportError("Ошибка чтения выходного файла", e.getMessage());
            throw e;
        } catch (Exception e) {
            reportError("Ошибка чтения входного файла", "Неизвестная ошибка\n" + e.getMessage());
            throw e;
        }
        current = new char[n][n];

        createInterface();
        reset();
        timer.start();
        updateInterface();
        /*
        final BufferedImage bufferedImage = new BufferedImage(SIZE + 1, SIZE + 1, BufferedImage.TYPE_INT_RGB);
        targetGrid.paint(bufferedImage.getGraphics());
        try {
            ImageIO.write(bufferedImage, "png", new File(image));
        } catch (IOException e) {
            throw new AssertionError(e);
        }
        */

    }

    Grid targetGrid;
    private void createInterface() {
        currentGrid = new Grid(current, true);
        targetGrid = new Grid(need, false);
        solutionLabel = new JLabel("Ваше решение", SwingConstants.CENTER);
        add(atop(
                aside(
                        atop(solutionLabel, currentGrid),
                        atop(new JLabel("Требуемый результат работы", SwingConstants.CENTER), targetGrid)
                ),
                createButtonsPane()
        ));
    }

    private JComponent aside(JComponent left, JComponent right) {
        final JPanel pane = new JPanel(new BorderLayout(30, 10));
        pane.add(left, BorderLayout.LINE_START);
        pane.add(right, BorderLayout.CENTER);
        return pane;
    }

    private JComponent atop(JComponent top, JComponent bottom) {
        final JPanel pane = new JPanel(new BorderLayout(3, 3));
        pane.add(top, BorderLayout.PAGE_START);
        pane.add(bottom, BorderLayout.CENTER);
        return pane;
    }

    private JPanel createButtonsPane() {
        JSlider sleepTime = createSleepSlider();

        mistakesHighlightButton = new JCheckBox(new AbstractAction("Показывать несовпадения") {
            @Override
            public void actionPerformed(ActionEvent e) {
                mistakesHighlight = !mistakesHighlight;
                mistakesHighlightButton.setSelected(mistakesHighlight);
                updateInterface();
            }
        });
        mistakesHighlightButton.setSelected(mistakesHighlight);

        JPanel pane = new JPanel(new GridBagLayout());
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.weightx = 1;
        gbc.fill = GridBagConstraints.BOTH;
        gbc.insets = INSETS;
        pane.add(new JButton(toBeginAction), gbc);
        pane.add(new JButton(stepBackAction), gbc);
        pane.add(new JButton(stepForwardAction), gbc);
        gbc.gridwidth = GridBagConstraints.REMAINDER;
        pane.add(new JButton(toEndAction), gbc);
        gbc.gridwidth = 1;
        pausedAction = new AbstractAction() {
            @Override
            public void actionPerformed(ActionEvent e) {
                setPaused(!paused);
            }
        };
        pane.add(new JButton(pausedAction), gbc);
        setPaused(true);
        gbc.gridwidth = GridBagConstraints.REMAINDER;
        pane.add(sleepTime, gbc);
        pane.add(mistakesHighlightButton, gbc);
        if (runningWithoutOutput) {
            pane.add(new JLabel("<html><font color='red'>Показываются только входные данные (выходной файл не найден)"), gbc);
        }
        return pane;
    }

    private JSlider createSleepSlider() {
        final JSlider slider = new JSlider(0, MAX_DELAY - 1, MAX_DELAY / 2);
        Hashtable<Integer, JLabel> labels = new Hashtable<>();
        labels.put(1, new JLabel("Медленно"));
        labels.put(MAX_DELAY - 1, new JLabel("Быстро"));
        slider.setLabelTable(labels);
        slider.setPaintLabels(true);
        slider.addChangeListener(new ChangeListener() {
            @Override
            public void stateChanged(ChangeEvent e) {
                timer.setDelay(MAX_DELAY - slider.getValue());
            }
        });
        timer.setDelay(MAX_DELAY - slider.getValue());
        return slider;
    }

    private void reportError(String title, String message) {
        JOptionPane.showMessageDialog(
                this,
                message,
                title,
                JOptionPane.ERROR_MESSAGE

        );
    }

    private void reset() {
        solutionPtr = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                current[i][j] = i != 0 || j != 0 ? 'W' : 'B';
        }
        curX = 0;
        curY = 0;
        error = false;
        setPaused(true);
    }

    private boolean inBounds(int x, int y) {
        return ((x >= 0) && (x < n) && (y >= 0) && (y < n));
    }

    private boolean oneStepForward() {
        if (isAtEnd()) {
            return false;
        }
        int j = getDirection();
        if (!inBounds(curX + dx[j], curY + dy[j])) {
            error = true;
            setPaused(true);
            reportError("Ошибка", "Решение вышло за границу поля");
            return false;
        }
        curX += dx[j];
        curY += dy[j];
        oldLog.addLast(current[curX][curY]);
        if (Character.isUpperCase(solution.charAt(solutionPtr))) {
            current[curX][curY] = current[curX - dx[j]][curY - dy[j]];
        }
        ++solutionPtr;
        updateInterface();
        return true;
    }

    private boolean isAtEnd() {
        return solutionPtr == solution.length();
    }

    private int getDirection() {
        return names.indexOf(Character.toLowerCase(solution.charAt(solutionPtr)));
    }

    void oneStepBackward() {
        if (isAtStart()) {
            return;
        }
        error = false;
        solutionPtr--;
        int j = names.indexOf(Character.toLowerCase(solution.charAt(solutionPtr)));
        current[curX][curY] = oldLog.removeLast();
        curX -= dx[j];
        curY -= dy[j];
        updateInterface();
    }

    final static int dx[] = { 1, 0, -1, 0 };
    final static int dy[] = { 0, 1, 0, -1 };
    final static String names = "drul";

    public void setPaused(boolean paused) {
        this.paused = paused;
        updateInterface();
    }

    private void updateInterface() {
        solutionLabel.setText("Ваше решение (шаг " + solutionPtr + " из " + solution.length() + ")");
        pausedAction.putValue(Action.NAME, paused ? "Старт" : "Стоп");
        toBeginAction.setEnabled(paused && !isAtStart());
        stepBackAction.setEnabled(paused && !isAtStart());
        stepForwardAction.setEnabled(paused && !isAtEnd() && !error);
        toEndAction.setEnabled(paused && !isAtEnd() && !error);
        currentGrid.repaint();
    }

    private boolean isAtStart() {
        return solutionPtr == 0;
    }

    class Grid extends JPanel {
        final char[][] values;
        final boolean showPos;

        Grid(char[][] values, boolean showPos) {
            this.values = values;
            this.showPos = showPos;
            setPreferredSize(new Dimension(SIZE + 1, SIZE + 1));
        }

        @Override
        public void paint(Graphics g) {
            g.clearRect(0, 0, SIZE + 1, SIZE + 1);
            int nSize = (SIZE) / n;
            g.clearRect(0, 0, SIZE / n * n, SIZE / n * n);

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    g.setColor(values[i][j] == 'B' ? Color.GRAY : Color.WHITE);
                    g.fillRect(j * nSize, i * nSize, nSize, nSize);
                    if (mistakesHighlight && values[i][j] != need[i][j]) {
                        g.setColor(Color.RED);
                        int l = j * nSize + nSize / 5;
                        int t = i * nSize + nSize / 5;
                        int r = (j + 1) * nSize - nSize / 5;
                        int b = (i + 1) * nSize - nSize / 5;
                        g.drawLine(l, t, r, b);
                        g.drawLine(r, t, l, b);
                    }
                }
            }

            g.setColor(Color.BLACK);

            for (int i = 0; i <= n; i++) {
                g.drawLine(0, i * nSize, n * nSize, i * nSize);
                g.drawLine(i * nSize, 0, i * nSize, n * nSize);
            }

            if (showPos) {
                g.setColor(Color.YELLOW);
                for (int k = 0; k < 2; k++)
                    g.drawRect(0 + curY * nSize + k, 0 + curX * nSize + k, nSize + 1 - 2 * k, nSize + 1 - 2 * k);
            }
        }
    }
}
