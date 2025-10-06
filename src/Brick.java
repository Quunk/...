import java.awt.Color;
import java.awt.Graphics;

public class Brick extends GameObject {
    private Color color;
    
    public Brick(int x, int y, int width, int height, Color color) {
        super(x, y, width, height);
        this.color = color;
    }
    
    @Override
    public void update() {
    }
    
    @Override
    public void render(Graphics g) {
        g.setColor(color);
        g.fillRect(x, y, width, height);
        g.setColor(Color.BLACK);
        g.drawRect(x, y, width, height);
    }
}
