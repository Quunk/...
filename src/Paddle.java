import java.awt.Color;
import java.awt.Graphics;

public class Paddle extends MovableObject {
    private static final int SPEED = 7;
    private int gameWidth;
    
    public Paddle(int x, int y, int width, int height, int gameWidth) {
        super(x, y, width, height);
        this.gameWidth = gameWidth;
    }
    
    public void moveLeft() {
        velocityX = -SPEED;
    }
    
    public void moveRight() {
        velocityX = SPEED;
    }
    
    public void stop() {
        velocityX = 0;
    }
    
    @Override
    public void update() {
        x += velocityX;
        
        if (x < 0) {
            x = 0;
        }
        if (x + width > gameWidth) {
            x = gameWidth - width;
        }
    }
    
    @Override
    public void render(Graphics g) {
        g.setColor(Color.BLUE);
        g.fillRect(x, y, width, height);
    }
}
