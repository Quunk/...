import javax.swing.JFrame;

public class Game {
    public static void main(String[] args) {
        JFrame frame = new JFrame("Arkanoid");
        GameManager gameManager = new GameManager();
        
        frame.add(gameManager);
        frame.setSize(GameManager.getGameWidth(), GameManager.getGameHeight());
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setResizable(false);
        frame.setLocationRelativeTo(null);
        frame.setVisible(true);
    }
}
