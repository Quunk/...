import java.awt.Color;
import java.awt.Graphics;

public class Ball extends MovableObject {
    private int gameWidth;
    private int gameHeight;
    
    public Ball(int x, int y, int size, int gameWidth, int gameHeight) {
        super(x, y, size, size);
        this.gameWidth = gameWidth;
        this.gameHeight = gameHeight;
        setVelocity(3, -3);
    }
    
    @Override
    public void update() {
        x += velocityX;
        y += velocityY;
        
        if (x <= 0 || x + width >= gameWidth) {
            velocityX = -velocityX;
            x = x <= 0 ? 0 : gameWidth - width;
        }
        
        if (y <= 0) {
            velocityY = -velocityY;
            y = 0;
        }
    }
    
    public void checkPaddleCollision(Paddle paddle) {
        if (getBounds().intersects(paddle.getBounds()) && velocityY > 0) {
            velocityY = -velocityY;
            y = paddle.getY() - height;
            
            int paddleCenter = paddle.getX() + paddle.getWidth() / 2;
            int ballCenter = x + width / 2;
            int offset = ballCenter - paddleCenter;
            velocityX += offset * 0.1;
        }
    }
    
    public boolean isOutOfBounds() {
        return y > gameHeight;
    }
    
    public void reset(int startX, int startY) {
        x = startX;
        y = startY;
        setVelocity(3, -3);
    }
    
    @Override
    public void render(Graphics g) {
        g.setColor(Color.RED);
        g.fillOval(x, y, width, height);
    }
}
