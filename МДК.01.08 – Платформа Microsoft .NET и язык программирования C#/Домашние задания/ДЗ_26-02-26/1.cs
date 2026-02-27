using System;

class Program
{
    static void Main()
    {
        int mapWidth = 10;
        int mapHeight = 10;

        int playerX = 0;
        int playerY = 0;

        Random random = new Random();
        int monsterX = random.Next(0, mapWidth);
        int monsterY = random.Next(0, mapHeight);

        while (playerX == monsterX && playerY == monsterY)
        {
            monsterX = random.Next(0, mapWidth);
            monsterY = random.Next(0, mapHeight);
        }

        int turns = 0;
        bool gameOver = false;

        while (!gameOver)
        {
            Console.Clear();

            for (int y = 0; y < mapHeight; y++)
            {
                for (int x = 0; x < mapWidth; x++)
                {
                    if (x == playerX && y == playerY)
                    {
                        Console.Write("P ");
                    }
                    else if (x == monsterX && y == monsterY)
                    {
                        Console.Write("M ");
                    }
                    else
                    {
                        Console.Write(". ");
                    }
                }
                Console.WriteLine();
            }

            Console.WriteLine("Ходов: " + turns);

            if (playerX == monsterX && playerY == monsterY)
            {
                Console.WriteLine("Игра окончена");
                gameOver = true;
                break;
            }

            if (turns >= 20)
            {
                Console.WriteLine("Победа");
                gameOver = true;
                break;
            }

            string input = Console.ReadLine();

            int newPlayerX = playerX;
            int newPlayerY = playerY;

            if (input == "w" || input == "W")
            {
                newPlayerY = playerY - 1;
            }
            else if (input == "s" || input == "S")
            {
                newPlayerY = playerY + 1;
            }
            else if (input == "a" || input == "A")
            {
                newPlayerX = playerX - 1;
            }
            else if (input == "d" || input == "D")
            {
                newPlayerX = playerX + 1;
            }

            if (newPlayerX >= 0 && newPlayerX < mapWidth && newPlayerY >= 0 && newPlayerY < mapHeight)
            {
                playerX = newPlayerX;
                playerY = newPlayerY;
            }

            int direction = random.Next(0, 4);
            int newMonsterX = monsterX;
            int newMonsterY = monsterY;

            if (direction == 0)
            {
                newMonsterY = monsterY - 1;
            }
            else if (direction == 1)
            {
                newMonsterY = monsterY + 1;
            }
            else if (direction == 2)
            {
                newMonsterX = monsterX - 1;
            }
            else if (direction == 3)
            {
                newMonsterX = monsterX + 1;
            }

            if (newMonsterX >= 0 && newMonsterX < mapWidth && newMonsterY >= 0 && newMonsterY < mapHeight)
            {
                monsterX = newMonsterX;
                monsterY = newMonsterY;
            }

            turns++;
        }
    }
}
