using System.Collections.Generic;

class Program
{
    static void Main()
    {
        FindMax();
        SumRange();
        MergeSortedLists();
        FindUniqueElements();
    }

    static void FindMax()
    {
        List<int> numbers = new List<int> { 3, 7, 2, 9, 1 };
        int max = numbers[0];
        for (int i = 1; i < numbers.Count; i++)
        {
            if (numbers[i] > max)
                max = numbers[i];
        }
        Console.WriteLine("Максимум: " + max);
    }

    static void SumRange()
    {
        int start = 1;
        int end = 5;
        if (start > end)
        {
            int temp = start;
            start = end;
            end = temp;
        }
        int sum = 0;
        for (int i = start; i <= end; i++)
        {
            sum += i;
        }
        Console.WriteLine($"Сумма от {start} до {end}: " + sum);
    }

    static void MergeSortedLists()
    {
        List<int> list1 = new List<int> { 1, 3, 5, 7 };
        List<int> list2 = new List<int> { 2, 4, 6, 8, 10 };
        List<int> merged = new List<int>();
        int i = 0, j = 0;
        while (i < list1.Count && j < list2.Count)
        {
            if (list1[i] <= list2[j])
            {
                merged.Add(list1[i]);
                i++;
            }
            else
            {
                merged.Add(list2[j]);
                j++;
            }
        }

        while (i < list1.Count)
        {
            merged.Add(list1[i]);
            i++;
        }

        while (j < list2.Count)
        {
            merged.Add(list2[j]);
            j++;
        }

        Console.WriteLine("Слияние: [" + string.Join(", ", merged) + "]");
    }

    static void FindUniqueElements()
    {
        List<int> numbers = new List<int> { 1, 2, 2, 3, 4, 4, 5 };
        List<int> unique = new List<int>();

        for (int i = 0; i < numbers.Count; i++)
        {
            int current = numbers[i];
            int count = 0;

            for (int j = 0; j < numbers.Count; j++)
            {
                if (numbers[j] == current)
                    count++;
            }

            if (count == 1)
            {
                bool alreadyAdded = false;
                for (int k = 0; k < unique.Count; k++)
                {                    if (unique[k] == current)
                    {
                        alreadyAdded = true;
                        break;
                    }
                }

                if (!alreadyAdded)
                    unique.Add(current);
            }
        }

        Console.WriteLine("Уникальные: [" + string.Join(", ", unique) + "]");
    }
}
