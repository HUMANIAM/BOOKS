package headFirst.designPatterns.Introduction;

import headFirst.designPatterns.Introduction.FlyBehavior;

public class FlyNoWay implements FlyBehavior{
    public void fly()
    {
        System.out.println("I can't fly");
    }
}
