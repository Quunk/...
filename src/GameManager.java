import javax.swing.JPanel;
import javax.swing.Timer;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.util.ArrayList;
import java.util.List;

public class GameManager extends JPanel implements ActionListener, KeyListener {
    private static final int WIDTH = 800;
    private static final int HEIGHT = 600;
    private static final int PADDLE_WIDTH = 100;
    private static final int PADDLE_HEIGHT = 15;
    private static final int BALL_SIZE = 15;
    private static final int BRICK_WIDTH = 75;
    private static final int BRICK_HEIGHT = 20;
    private static final int BRICK_ROWS = 5;
    private static final int BRICK_COLS = 10;
    
    private Timer timer;
    private Paddle paddle;
    private Ball ball;
    private List<Brick> bricks;
    private boolean running;
    
    public GameManager() {
        setFocusable(true);
        addKeyListener(this);
        setBackground(Color.BLACK);
        
        initGame();
        
        timer = new Timer(16, this);
        timer.start();
        running = true;
    }
    
    private void initGame() {
        paddle = new Paddle(WIDTH / 2 - PADDLE_WIDTH / 2, HEIGHT - 50, PADDLE_WIDTH, PADDLE_HEIGHT, WIDTH);
        ball = new Ball(WIDTH / 2 - BALL_SIZE / 2, HEIGHT / 2, BALL_SIZE, WIDTH, HEIGHT);
        
        bricks = new ArrayList<>();
        Color[] colors = {Color.RED, Color.ORANGE, Color.YELLOW, Color.GREEN, Color.CYAN};
        
        int offsetX = 10;
        int offsetY = 50;
        
        for (int row = 0; row < BRICK_ROWS; row++) {
            for (int col = 0; col < BRICK_COLS; col++) {
                int x = offsetX + col * (BRICK_WIDTH + 5);
                int y = offsetY + row * (BRICK_HEIGHT + 5);
                bricks.add(new Brick(x, y, BRICK_WIDTH, BRICK_HEIGHT, colors[row]));
            }
        }
    }
    
    @Override
    public void actionPerformed(ActionEvent e) {
        if (running) {
            update();
        }
        repaint();
    }
    
    private void update() {
        paddle.update();
        ball.update();
        ball.checkPaddleCollision(paddle);
        
        if (ball.isOutOfBounds()) {
            ball.reset(WIDTH / 2 - BALL_SIZE / 2, HEIGHT / 2);
        }
    }
    
    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        
        paddle.render(g);
        ball.render(g);
        
        for (Brick brick : bricks) {
            brick.render(g);
        }
    }
    
    @Override
    public void keyPressed(KeyEvent e) {
        int key = e.getKeyCode();
        
        if (key == KeyEvent.VK_LEFT || key == KeyEvent.VK_A) {
            paddle.moveLeft();
        }
        if (key == KeyEvent.VK_RIGHT || key == KeyEvent.VK_D) {
            paddle.moveRight();
        }
    }
    
    @Override
    public void keyReleased(KeyEvent e) {
        int key = e.getKeyCode();
        
        if (key == KeyEvent.VK_LEFT || key == KeyEvent.VK_A || 
            key == KeyEvent.VK_RIGHT || key == KeyEvent.VK_D) {
            paddle.stop();
        }
    }
    
    @Override
    public void keyTyped(KeyEvent e) {
    }
    
    public static int getGameWidth() {
        return WIDTH;
    }
    
    public static int getGameHeight() {
        return HEIGHT;
    }
}
