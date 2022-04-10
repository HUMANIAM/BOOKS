import headFirst.designPatterns.Introduction.QuackBehavior;

public class MuteQuack implements QuackBehavior{
    public void quack()
    {
        System.out.println("<< Silence >>");
    }
}
