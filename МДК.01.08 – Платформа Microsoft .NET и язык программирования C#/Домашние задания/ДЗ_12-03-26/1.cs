using System;

class Rectangle
{
    public double width;
    public double height;

    public double GetArea()
    {
        return width * height;
    }

    public double GetPerimeter()
    {
        return 2 * (width + height);
    }
}

class Program
{
    static void Main()
    {
        Rectangle rect1 = new Rectangle();
        rect1.width = 4;
        rect1.height = 8;
        double area1 = rect1.GetArea();
        double perimeter1 = rect1.GetPerimeter();
        Console.WriteLine("Прямоугольник 1: " +
            "\nШирина: " + rect1.width + 
            "\nВысота: " + rect1.height + 
            "\nПлощадь: " + area1 + 
            "\nПериметр: " + perimeter1);

        Rectangle rect2 = new Rectangle();
        rect2.width = 44;
        rect2.height = 88;
        double area2 = rect2.GetArea();
        double perimeter2 = rect2.GetPerimeter();
        Console.WriteLine("\nПрямоугольник 2: " +
            "\nШирина: " + rect2.width +
            "\nВысота: " + rect2.height +
            "\nПлощадь: " + area2 +
            "\nПериметр: " + perimeter2);
    }
}
