using System;
using System.Collections.Generic;

class Program
{
    static void Main()
    {
        Dictionary<string, int> shopItems = new Dictionary<string, int>
        {
            { "Health Potion", 50 },
            { "Mana Potion", 75 },
            { "Sword", 200 },
            { "Shield", 150 }
        };

        while (true)
        {
            Console.WriteLine("1. Показать всё");
            Console.WriteLine("2. Добавить или изменить");
            Console.WriteLine("3. Удалить");
            Console.WriteLine("4. Купить");
            Console.WriteLine("5. Выйти");
            Console.Write("Выберите пункт: ");

            string action = Console.ReadLine();

            if (action == "1")
            {
                Console.WriteLine("\nСписок товаров:");
                foreach (var item in shopItems)
                {
                    Console.WriteLine(item.Key + " - " + item.Value + " монет");
                }
            }
            else if (action == "2")
            {
                Console.Write("Введите название товара: ");
                string name = Console.ReadLine();
                Console.Write("Введите цену: ");
                int price = int.Parse(Console.ReadLine());

                shopItems[name] = price;
                Console.WriteLine("Готово");
            }
            else if (action == "3")
            {
                Console.Write("Какой товар удалить: ");
                string name = Console.ReadLine();
                shopItems.Remove(name);
                Console.WriteLine("Товар удален");
            }
            else if (action == "4")
            {
                Console.Write("Какой товар купить: ");
                string name = Console.ReadLine();

                bool found = false;
                foreach (var item in shopItems)
                {
                    if (item.Key == name)
                    {
                        Console.Write("Сколько штук: ");
                        int count = int.Parse(Console.ReadLine());
                        int total = item.Value * count;
                        Console.WriteLine("Общая стоимость: " + total);
                        found = true;
                        break;
                    }
                }

                if (found == false)
                {
                    Console.WriteLine("Такого товара нет");
                }
            }
            else if (action == "5")
            {
                break;
            }
        }
    }
}
