package headFirst.designPatterns.Introduction;

import headFirst.designPatterns.Introduction.Duck;
import headFirst.designPatterns.Introduction.FlyWithWings;
import headFirst.designPatterns.Introduction.QuackBehavior;

public class MallardDuck extends Duck
{
    public MallardDuck()
    {
        quackBehavior = new Quack();
        flyBehavior = new FlyWithWings();
    }    

    public void display()
    {
        System.out.println("I am a real Mallard duck.");
    }
}
