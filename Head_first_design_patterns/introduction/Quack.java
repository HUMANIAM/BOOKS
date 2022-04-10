package headFirst.designPatterns.Introduction;

import headFirst.designPatterns.Introduction.QuackBehavior;

public class Quack implements QuackBehavior
{
    public void quack()
    {
        System.out.println("Quack");
    }
}
