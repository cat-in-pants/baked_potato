using System;

class Game
{
    static string secret = "штаны";
    static void Main()
    {
        char[] mask = { '_', '_', '_', '_', '_' };
        int attemptsLeft = 6;
        while (attemptsLeft > 0)
        {
            Console.WriteLine(new string(mask));
            Console.WriteLine("Попыток осталось: " + attemptsLeft);
            Console.Write("Введите букву: ");
            char inputChar = Console.ReadKey().KeyChar;
            Console.WriteLine();

            if (!ProcessGuess(inputChar, mask)) attemptsLeft--;

            if (mask[0] != '_' && mask[1] != '_' && mask[2] != '_' && mask[3] != '_' && mask[4] != '_')
            {
                Console.WriteLine("Победа! Слово было: штаны");
                return;
            }
        }
        Console.WriteLine("Поражение. Загаданное слово: штаны");
    }
    static bool ProcessGuess(char letter, char[] maskedWord)
    {
        bool found = false;
        for (int position = 0; position < secret.Length; position++)
        {
            if (secret[position] == letter)
            {
                maskedWord[position] = letter;
                found = true;
            }
        }
        return found;
    }
}
