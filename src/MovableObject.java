public abstract class MovableObject extends GameObject {
    protected double velocityX;
    protected double velocityY;
    
    public MovableObject(int x, int y, int width, int height) {
        super(x, y, width, height);
        this.velocityX = 0;
        this.velocityY = 0;
    }
    
    public void setVelocity(double vx, double vy) {
        this.velocityX = vx;
        this.velocityY = vy;
    }
    
    public double getVelocityX() {
        return velocityX;
    }
    
    public double getVelocityY() {
        return velocityY;
    }
}
